{-# LANGUAGE FlexibleInstances #-}
import Data.Time.Format.ISO8601 (yearFormat)

-- 1
data Mes = Enero | Febrero | Marzo | Abril | Mayo | Junio | Julio | Agosto | Septiembre | Octubre | Noviembre | Diciembre deriving (Show)

vacaciones :: Mes -> Bool
vacaciones Enero = False
vacaciones Febrero = False
vacaciones Julio = False
vacaciones Diciembre = False
vacaciones _ = True

-- 2

data Forma = Circulo Float | Rectangulo Float Float | Triangulo Float Float Float deriving (Show)

perimetro :: Forma -> Float
perimetro (Circulo r) = 3.14 * 2 * r
perimetro (Rectangulo l1 l2) = 2 * (l1 + l2)
-- 3
perimetro (Triangulo l1 l2 l3) = l1 + l2 + l3

-- 4

escalar :: Float -> Forma -> Forma
escalar n (Circulo r) = Circulo (n * r)
escalar n (Rectangulo l1 l2) = Rectangulo (n * l1) (n * l2)
escalar n (Triangulo l1 l2 l3) = Triangulo (n * l1) (n * l2) (n * l3)

-- 5

data Dinero = Dolar Float | Peso Float | Cheque String Dinero deriving (Show)

convertir :: Dinero -> Dinero
convertir (Dolar x) = Peso (x * 1190)
convertir (Peso x) = Dolar (x / 1190)

-- 6

cheques :: Dinero -> Dinero
cheques (Cheque lagajo plata) = Cheque lagajo plata

-- 7

data Nat = Zero | Succ Nat deriving (Show)

nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Succ nro) = 1 + nat2int nro

-- 8

data List a = Nil | Cons a (List a) deriving (Show)

sumar' :: List Int -> Int
sumar' Nil = 0
sumar' (Cons x xs) = x + sumar' xs

-- 9

data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr deriving (Show)

expresion :: Expr
expresion = Resta (Suma (Literal 1) (Literal 2)) (Suma (Literal 3) (Literal 4))

-- 10

mostrar :: Expr -> String
mostrar (Literal a) = show a
mostrar (Suma a1 a2) = "(" ++ mostrar a1 ++ "+" ++ mostrar a2 ++ ")"
mostrar (Resta a1 a2) = "(" ++ mostrar a1 ++ "-" ++ mostrar a2 ++ ")"

evaluar :: Expr -> Int
evaluar (Literal a) = a
evaluar (Suma a1 a2) = evaluar a1 + evaluar a2
evaluar (Resta a1 a2) = evaluar a1 - evaluar a2

-- 11

buscar :: Int -> Expr -> Bool
buscar n (Literal a) = n == a
buscar n (Suma a1 a2) = buscar n a1 || buscar n a2
buscar n (Resta a1 a2) = buscar n a1 || buscar n a2

-- 12

list2alg :: [a] -> List a
list2alg [] = Nil
list2alg (x : xs) = Cons x (list2alg xs)

-- 13

divisionSegura :: Float -> Float -> Maybe Float
divisionSegura _ 0 = Nothing
divisionSegura a1 a2 = Just (a1 / a2)

-- 14

join :: (a -> c) -> (b -> d) -> Either a b -> Either c d
join f _ (Left a) = Left (f a)
join _ f (Right a) = Right (f a)

-- 15

type Resultado a = Either a String

-- 16

llamarDiv :: Float -> Float -> Resultado Float
llamarDiv a1 a2 = transformar (divisionSegura a1 a2)
  where
    transformar (Just r) = Left r
    transformar Nothing = Right "Division por cero"

-- PRACTICA DE FOLDS

-- 1

foldNat :: (r -> r) -> r -> Nat -> r
foldNat f b Zero = b
foldNat f b (Succ n) = f (foldNat f b n)

foldList :: (a -> r -> r) -> r -> List a -> r
foldList f b Nil = b
foldList f b (Cons x xs) = f x (foldList f b xs)

-- 2

nat2int2 :: Nat -> Int
nat2int2 nro = foldNat (1 +) 0 nro

sumar2' :: List Int -> Int
sumar2' (Cons x xs) = foldList (+) 0 (Cons x xs)

list2alg2 :: [a] -> List a
list2alg2 = foldr Cons Nil

-- 3

foldExpr :: (r -> r -> r) -> (r -> r -> r) -> (Int -> r) -> Expr -> r
foldExpr s r l (Literal n) = l n
foldExpr s r l (Suma n1 n2) = s (foldExpr s r l n1) (foldExpr s r l n2)
foldExpr s r l (Resta n1 n2) = r (foldExpr s r l n1) (foldExpr s r l n2)

-- 4

mostrar2 :: Expr -> String
mostrar2 = foldExpr (\x y -> "(" ++ x ++ "+" ++ y ++ ")") (\x y -> "(" ++ x ++ "-" ++ y ++ ")") show

evaluar2 :: Expr -> Int
evaluar2 = foldExpr (+) (-) id

buscar2 :: Int -> Expr -> Bool
buscar2 k = foldExpr (||) (||) (== k)

-- 5

natSize :: List a -> Nat
natSize l = foldList (\a x -> Succ x) Zero l

-- 6

dup :: List a -> List a
dup l = foldList (\x y -> Cons x (Cons x y)) Nil l

-- 7

zipdup :: List a -> List (a, a)
zipdup = foldList (\x l -> Cons (x, x) l) Nil

-- 8

concatenar :: List a -> List a -> List a
concatenar l1 l2 = foldList (\x l -> (Cons x) l) l2 l1

flattenExpr :: Expr -> List Int
flattenExpr expr = foldExpr concatenar concatenar (\x -> Cons x Nil) expr

-- 9

maxNumber :: Expr -> Int
maxNumber expr = foldExpr max max id expr

-- 10

repeat' :: a -> Nat -> List a
repeat' n l = foldNat (\x -> Cons n x) Nil l

-- 11

mapList :: (a -> b) -> List a -> List b
mapList f l = foldList (\x y -> Cons (f x) y) Nil l

filterList :: (a -> Bool) -> List a -> List a
filterList f list = foldList (\x y -> if (f x) then Cons x y else y) Nil list

-- 12

data Traza = Izquierda Traza | Derecha Traza | Adelante Traza | Nothing' deriving (Show)

foldTraza :: (r -> r) -> (r -> r) -> (r -> r) -> r -> Traza -> r
foldTraza i d a n Nothing' = n
foldTraza i d a n (Izquierda x) = i (foldTraza i d a n x)
foldTraza i d a n (Derecha x) = d (foldTraza i d a n x)
foldTraza i d a n (Adelante x) = a (foldTraza i d a n x)

-- 13

flattenList :: List (List a) -> List a
flattenList list = foldList concatenar Nil list

listasListas :: List (List Int)
listasListas =
  Cons
    (Cons 1 (Cons 2 Nil))
    ( Cons
        (Cons 3 (Cons 4 Nil))
        (Cons (Cons 5 (Cons 6 Nil)) Nil)
    )

resultado :: List Int
resultado = flattenList listasListas

-- 14

listafib :: [(Int, Int)] -> Bool
listafib fib = let (_, _, x) = listaFib fib in x
  where
    listaFib = foldl next init
    next (a, b, x) (c, d) = let isFib = x && b == c && d == a + b in (c, d, isFib)
    init = (0, 1, True)

-- ????? no me anduvo

-- 15

data Fib = FStep (Int, Int) Fib | FEmpty deriving (Show)

foldFib :: (Int -> Int -> r -> r) -> r -> Fib -> r
foldFib _ e FEmpty = e
foldFib f e (FStep (x, y) fibnext) = f x y (foldFib f e fibnext)

-- 16


-- Clases e Instancias 

--1

iguales :: Eq a => a -> a -> Bool
iguales x y = not (x /= y)

desiguales :: Eq a => a -> a -> Bool
desiguales x y = not (x == y)

--2

numEqual :: Eq a => a -> [a] -> Int
numEqual k [] = 0
numEqual k (x:xs) = if (k == x) then 1 + numEqual k xs else numEqual k xs

--3

--4

--5

class Visible a where
    toString :: a -> String
    size     :: a -> Int

cmp :: Visible a => a -> a -> Bool
cmp x y = size x <= size y

--6

compareOrd :: Ord a => a -> a -> Ordering
compareOrd x y
    | x <= y && y <= x = EQ
    | x <= y && not (y <= x) = LT
    | otherwise = GT

menorOrd :: Ord a => a -> a -> Bool
menorOrd x y  = (compareOrd x y) == LT

menoroigualOrd :: Ord a => a -> a -> Bool
menoroigualOrd x y = (compareOrd x y) == LT || (compareOrd x y) == EQ

mayorOrd :: Ord a => a -> a -> Bool
mayorOrd x y = (compareOrd x y) == GT

mayoroigualOrd :: Ord a => a -> a -> Bool
mayoroigualOrd x y = (compareOrd x y) == GT || (compareOrd x y) == EQ

maxOrd :: Ord a => a -> a -> a
maxOrd x y
    |x <= y = y
    |otherwise = x

minOrd :: Ord a => a -> a -> a
minOrd x y
    |x <= y = x
    |otherwise = y


--7 da error porque ya se definio en el preludio de haskell
--instance Ord a => Ord [a] where 
--    [] <= _ = True
--    _ <= [] = False
--    (x:xs) <= (y:ys) 
--        |x < y = True
--        |x > y = False
--        |otherwise = xs <= ys
 
--9

instance Eq a => Eq (Bool -> a) where
    (==) :: Eq a => (Bool -> a) -> (Bool -> a) -> Bool
    f == g = f True == g True && f False == g False

eqdeNot :: Bool
eqdeNot = not == not

eqdeId :: Bool
eqdeId = id == (id :: Bool -> Bool)

eqdeAnd :: Bool
eqdeAnd = (&&) == (&&)

eqdeOr :: Bool
eqdeOr = (||) == (||)

--10

class Geometrico figura where
    perimetro' :: figura -> Float
    area' :: figura -> Float

data Punto = Punto Float Float deriving (Show)

instance Geometrico Punto where
    perimetro' :: Punto -> Float
    perimetro' _ = 0
    area' :: Punto -> Float
    area' _ = 0

data Linea = Linea Punto Punto deriving (Show)

instance Geometrico Linea where
    perimetro' :: Linea -> Float
    perimetro' (Linea (Punto x1 y1) (Punto x2 y2)) = sqrt ((x2 - x1) ^ 2 + (y2 - y1) ^ 2)
    area' :: Linea -> Float
    area' _ = 0

--data Forma = Circulo Float | Rectangulo Float Float | Triangulo Float Float Float deriving (Show)


instance Geometrico Forma where
    perimetro' :: Forma -> Float
    perimetro' (Circulo r) = 3.14 * r * 2
    perimetro' (Rectangulo l1 l2) = 2 * (l1 + l2)
    perimetro' (Triangulo l1 l2 l3) = l1 + l2 + l3
    area' :: Forma -> Float
    area' (Circulo r) = 3.14 * r ^ 2
    area' (Rectangulo l1 l2 ) = l1 * l2
    area' (Triangulo l1 l2 l3) = let semiperimetro = (l1 + l2 + l3) / 2
                                 in sqrt (semiperimetro * (semiperimetro - l1) * (semiperimetro - l2) * (semiperimetro - l3))

dimension :: Geometrico f => f -> Int
dimension f
    |perimetro' f == 0 && area' f == 0 = 0
    |area' f == 0 = 1
    |otherwise = 2    