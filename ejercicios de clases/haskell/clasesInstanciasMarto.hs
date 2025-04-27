import Data.Char (toLower)

igual :: (Eq a) => a -> a -> Bool
igual a b = not (a /= b)

desigualdad :: (Eq a) => a -> a -> Bool
desigualdad a b = not (a == b)

numEqual :: (Eq a) => [a] -> a -> Int
numEqual xs a = foldr (\x acc -> if (x == a) then (1 + acc) else acc) 0 xs

data Prueba = Primero Int | Segundo String deriving (Show)

instance Eq Prueba where
  (==) :: Prueba -> Prueba -> Bool
  Primero a == Primero y = a == y
  Segundo x == Segundo y = x == y
  _ == _ = False

numEqualEjemplo :: Int
numEqualEjemplo = numEqual [Primero 1, Primero 2, Primero 1, Segundo "hola", Segundo "hoLa"] (Segundo "hola")

class Visible a where
  toString :: a -> String
  size :: a -> Int

cmp :: (Visible a) => a -> a -> Bool
cmp x y = size x <= size y

instance Visible Int where
  toString = show
  size = abs

instance Visible String where
  toString :: String -> String
  toString x = x
  size :: String -> Int
  size xs = foldr (\a b -> 1 + b) 0 xs

instance (Eq a) => Eq (Bool -> a) where
  (==) :: (Eq a) => (Bool -> a) -> (Bool -> a) -> Bool
  f == g = f True == g True && f False == g False
