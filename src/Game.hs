module Game where

import Camera
import Coordinate
import Control.Lens
import Control.Monad.State as S
import Object
import SDL
import World

-- | Contains the state of the game (things that will change over time)
data Game = MkGame
    { _gamePlayer  :: ObjectId
    , _gameCamera  :: Camera
    , _gameWorld   :: World
    }

-- Lenses
gameCamera :: Lens' Game Camera
gameWorld :: Lens' Game World
gamePlayer :: Lens' Game ObjectId
gameCamera f s = (\x -> s { _gameCamera = x }) <$> f (_gameCamera s)
gameWorld f s = (\x -> s { _gameWorld = x }) <$> f (_gameWorld s)
gamePlayer f s = (\x -> s { _gamePlayer = x }) <$> f (_gamePlayer s)

-- | Default game state with an empty world, player and camera at 0,0
defaultGame :: Game
defaultGame = MkGame
    { _gamePlayer  = 2 -- TODO: change back to 0
    , _gameCamera  = defaultCamera
    , _gameWorld   = defaultWorld
    }

-- | This function takes care of all events in the game and dispatches them to the appropriate handlers.
gameHandleEvent :: Event -> State Game Bool
gameHandleEvent event =
    case eventPayload event of
        KeyboardEvent ked -> gameHandleKeyboardEvent ked
        QuitEvent         -> return True
        _                 -> return False

-- | This function handles keyboard events in the game
gameHandleKeyboardEvent :: KeyboardEventData -> State Game Bool
gameHandleKeyboardEvent ked = do
    player <- (^. gamePlayer) <$> S.get
    when (keymotion == Pressed) $ do
        case keycode of
            KeycodeUp    -> modify $ gameCamera %~ cameraMove UpDirection
            KeycodeDown  -> modify $ gameCamera %~ cameraMove DownDirection
            KeycodeRight -> modify $ gameCamera %~ cameraMove RightDirection
            KeycodeLeft  -> modify $ gameCamera %~ cameraMove LeftDirection
            KeycodeW     -> modify $ gameWorld  %~ thingMove UpDirection    player
            KeycodeS     -> modify $ gameWorld  %~ thingMove DownDirection  player
            KeycodeA     -> modify $ gameWorld  %~ thingMove LeftDirection  player
            KeycodeD     -> modify $ gameWorld  %~ thingMove RightDirection player
            KeycodeT     -> modify $ gameWorld  %~ worldTestInteractAll
            _            -> return ()
    return $ scancode == ScancodeEscape
    where
        keymotion   = keyboardEventKeyMotion ked -- ^ Wether the key is being pressed or released
        keysym      = keyboardEventKeysym ked    -- ^ Key symbol information: keycode or scancode representation
        keycode     = keysymKeycode keysym       -- ^ Which character is received from the operating system
        scancode    = keysymScancode keysym      -- ^ Physical key location as it would be on a US QWERTY keyboard
