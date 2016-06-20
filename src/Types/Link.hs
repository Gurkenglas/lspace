{-# LANGUAGE ExistentialQuantification #-}

module Types.Link where

import Data.IORef
import System.Mem.Weak

data Linkage = forall a. Link a
data Link a = LinkId Int | LinkRef Int (Weak (IORef a))
