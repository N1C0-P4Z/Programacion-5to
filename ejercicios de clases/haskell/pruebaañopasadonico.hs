import Text.XHtml (rev)
--1

--a

data OpEd = Escribir Char | Reemplazar Char | Borrar 

--b

aplicar :: OpEd -> String -> String 
aplicar (Borrar) s = init s
aplicar (Escribir c) s = s ++ [c]
aplicar (Reemplazar c) s = init s ++ [c]

--c

data List a = Nil | Cons a (List a) deriving (Show)

foldList :: (a -> r -> r) -> r -> List a -> r
foldList f b Nil = b
foldList f b (Cons x xs) = f x (foldList f b xs)


snoc :: List a -> a -> List a
snoc l x = foldList Cons (Cons x Nil) l 

reverseList :: List a -> List a
reverseList xs = foldList (\ x y -> y `snoc`x) Nil xs

aplicarTodas :: List OpEd -> String -> String 
aplicarTodas l s = foldList (\ l' s' -> aplicar l' s') s (reverseList l) 

--2 
--a

data Raro a = Nada | Algo a | Par (Raro a) (Raro a) 

foldRaro :: (r -> r -> r) -> (a -> r) -> r -> Raro a -> r 
foldRaro par algo nd (Nada) = nd
foldRaro par algo nd (Algo a) = algo a
foldRaro par algo nd (Par x y) = par (foldRaro par algo nd x) (foldRaro par algo nd y)

--b 

sumarRaro :: Raro Int -> Int 
sumarRaro raro = foldRaro (\ x y -> x + y) id 0 raro

--3

class Bolsa b where
    agregar :: a -> b a -> b a
    buscar :: Eq a => a -> b a -> Bool
    quitar :: Eq a => a -> b a -> b a
    cantidad :: b a -> Int

instance Bolsa List where
    agregar :: a -> List a -> List a
    agregar x l = (Cons x) l
    buscar :: Eq a => a -> List a -> Bool
    buscar x l = foldList (\y z -> if (x == y) then (True || z) else (False || z)) False l
    quitar :: Eq a => a -> List a -> List a
    quitar x l = foldList (\ y z -> if (x == y) then z else (Cons y z)) Nil l
    cantidad :: List a -> Int
    cantidad l = foldList (\ _ x -> 1 + x) 0 l

--4

fun :: Ord r => (a -> r) -> a -> r -> r -> r
fun g a s d 
    |g a == s = s 
    |g a < s = g a 
    |otherwise = d

-- PRUEBA RECUPEARATORIO: TIPOS ALGEBRAICOS; FOLDS Y CLASES

--1

--a

data CType = CInt | CPtr CType deriving (Show)

--b

-- **int :: CType
-- **int = CPtr (CPtr CInt)

--c

foldCType :: (r -> r) -> r -> CType  -> r
foldCType ptr entero (CInt) = entero
foldCType ptr entero (CPtr x) = ptr (foldCType ptr entero x) 

--d

accesosRAM :: CType -> Int
accesosRAM l = foldCType (\ x -> x + 1) 0 l 

--2
--a

data Nat = Zero | Succ Nat deriving (Show)


foldNat :: r -> (r -> r) -> Nat -> r
foldNat z su (Zero) = z
foldNat z su (Succ x) = su (foldNat z su x)

class Enum' a where
    succ'        :: a -> a
    toEnum'      :: Int -> a
    fromEnum    :: a -> Int

instance Enum' Nat where
    succ' :: Nat -> Nat
    succ' x = (Succ x) 
    toEnum' :: Int -> Nat
    toEnum' 0 = Zero
    toEnum' x = Succ (toEnum' x) 
    fromEnum :: Nat -> Int
    fromEnum x = foldNat 0 (+ 1) x

--b

enumFrom' :: Enum' a => a -> [a]
enumFrom' nro = nro : enumFrom' (succ' nro)

--4
fun' :: (Eq a, Eq b) => a -> b -> b -> b -> Bool
fun' t s b c = t == s || b == c
