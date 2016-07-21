{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE DeriveFunctor #-}

module Link where

import qualified Data.Aeson as J
import Data.IORef
import Data.Sequence as S
import qualified Data.ByteString.Lazy as LB
import System.Directory
import System.Mem.Weak

import Types.Cache
import Types.Link

-- trace :: b -> a -> a
-- trace = const id

-- New %~ lens combinator that's strict (thanks to puregreen)
data Id a = Id {runId :: !a} deriving Functor
(%~!) :: ((a -> Id b) -> c -> Id d) -> (a -> b) -> c -> d
l %~! f = runId . l (Id . f)

readLink :: forall a. J.FromJSON a => IORef Cache -> Link a -> IO (Maybe a)
readLink refCache (MkLink link) = do
    -- Read the link unsafe bastraction
    (i, r) <- readIORef link
    case r of
        -- Determines if we have a link reference
        Nothing -> do
            result <- loadFreshLinkId i
            case result of
                Nothing -> return Nothing
                Just a  -> do
                    -- writeIORef link a
                    modifyIORef' link $ const a
                    readLink refCache $ MkLink link
        Just x  -> do
            final <- deRefWeak x
            -- Does the reference point to something that still exists
            case final of
                Just z  -> do
                    v <- readIORef z
                    return $ Just v
                Nothing -> do
                    result <- loadFreshLinkId i
                    case result of
                        Nothing -> return Nothing
                        Just a  -> do
                            -- writeIORef link a
                            modifyIORef' link $ const a
                            readLink refCache $ MkLink link
    where
        loadFreshLinkId :: Int -> IO (Maybe (Int, Maybe (Weak (IORef a))))
        loadFreshLinkId i = do
            ok <- doesFileExist filepath
            if ok
            then do
                json <- LB.readFile filepath
                case J.decode json of
                    Nothing -> do
                        return Nothing
                    Just d  -> do
                        ref <- newIORef d

                        modifyIORef' refCache $ cacheLinks %~! \links -> (
                                                if S.length links >= maxLinks
                                                then S.drop 1 links
                                                else links
                                              ) |> MkAnyIORef ref

                        weakRef <- mkWeakIORef ref (return ())
                        return . Just $ (i, Just weakRef)
            else do
                return Nothing
            where
                filepath = "data/demo/" ++ show i ++ ".json" -- TODO: This has to be fixed
                maxLinks = 1000
