data CType = Literal Int | Puntero CType

var :: CType
var = Puntero (Puntero (Literal 12))

foldCtype :: (r -> r) -> (Int -> r) -> CType -> r
foldCtype p l (Literal a) = l a
foldCtype p l (Puntero xs) = p (foldCtype p l xs)

accesoRam :: CType -> Int
accesoRam = foldCtype (1 +) (const 1)

data Nat = Zero | Succ Nat deriving (Show)

foldNat :: (r -> r) -> r -> Nat -> r
foldNat f b Zero = b
foldNat f b (Succ xs) = f (foldNat f b xs)

class Enum' a where
  succ' :: a -> a
  toEnum' :: Int -> a
  fromEnum' :: a -> Int

instance Enum' Nat where
  succ' :: Nat -> Nat
  succ' = Succ

  toEnum' :: Int -> Nat
  toEnum' 0 = Zero
  toEnum' num = Succ (toEnum' (num - 1))

  fromEnum' :: Nat -> Int
  fromEnum' = foldNat (1 +) 0

enumFrom' :: (Enum' a) => a -> [a]
enumFrom' x = x : enumFrom' (succ' x)
