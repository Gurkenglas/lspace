module Object where

import Types.Coordinate
import Types.Object
import Types.Sprite

objSprite :: Object -> Sprite
objSprite (MkObject _ (ObjectBox box)) = case _boxState box of
    BoxClosed -> sprite 0 0 ZOnGround
objSprite (MkObject _ ObjectFloor) = sprite 4 1 ZGround
objSprite (MkObject _ ObjectPlant) = sprite 0 1 ZOnGround
objSprite (MkObject common (ObjectPlayer _)) = case objFacing common of
    North -> sprite 1 0 ZOnTop
    South -> sprite 1 2 ZOnTop
    West  -> sprite 1 1 ZOnTop
    East  -> sprite 1 3 ZOnTop
objSprite (MkObject _ (ObjectWall w)) = case _wallType w of
    WallTypeHorizontal -> sprite 5 2 ZGround
objSprite _ = defaultSprite
