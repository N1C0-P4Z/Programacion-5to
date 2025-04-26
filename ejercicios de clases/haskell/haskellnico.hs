{-# LANGUAGE FlexibleInstances #-}

--1
data Mes = Enero | Febrero | Marzo | Abril | Mayo | Junio | Julio | Agosto | Septiembre | Octubre | Noviembre | Diciembre deriving (Show)

vacaciones :: Mes -> Bool
vacaciones Enero = False
vacaciones Febrero = False
vacaciones Julio = False
vacaciones Diciembre = False
vacaciones _ = True

--2 

data Forma = Circulo Float | Rectangulo Float Float | Triangulo Float Float Float deriving (Show)

perimetro :: Forma -> Float
perimetro (Circulo r) = 3.14 * 2 * r
perimetro (Rectangulo l1 l2) = 2 * (l1 + l2)
--3
perimetro (Triangulo l1 l2 l3) = l1 + l2 + l3

--4

escalar :: Float -> Forma -> Forma
escalar n (Circulo r) = Circulo (n * r)
escalar n (Rectangulo l1 l2) = Rectangulo (n * l1) (n * l2)
escalar n (Triangulo l1 l2 l3) = Triangulo (n * l1) (n * l2) (n * l3)

--5

data Dinero = Dolar Float | Peso Float | Cheque String Dinero deriving (Show)

convertir :: Dinero -> Dinero
convertir (Dolar x) = Peso (x * 1190)
convertir (Peso x) = Dolar (x / 1190)

--6 

cheques :: Dinero -> Dinero
cheques (Cheque lagajo plata) = Cheque lagajo plata

--7

data Nat = Zero | Succ Nat deriving (Show)

nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Succ nro) = 1 + nat2int nro

--8

data List a = Nil | Cons a (List a) deriving (Show)

sumar' :: List Int -> Int
sumar' Nil = 0
sumar' (Cons x xs) = x + sumar' xs

-- 9

data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr deriving (Show)

expresion :: Expr
expresion = Resta(Suma (Literal 1) (Literal 2)) (Suma (Literal 3) (Literal 4))

--10

mostrar :: Expr -> String
mostrar (Literal a) = show a
mostrar (Suma a1 a2) = "(" ++ mostrar a1 ++ "+" ++ mostrar a2 ++ ")"
mostrar (Resta a1 a2) = "(" ++ mostrar a1 ++ "-" ++ mostrar a2 ++ ")"

evaluar :: Expr -> Int
evaluar (Literal a) = a
evaluar (Suma a1 a2) = evaluar a1 + evaluar a2
evaluar (Resta a1 a2) = evaluar a1 - evaluar a2

--11

buscar :: Int -> Expr -> Bool
buscar n (Literal a) = n == a
buscar n (Suma a1 a2) = buscar n a1 || buscar n a2
buscar n (Resta a1 a2) = buscar n a1 || buscar n a2

--12

list2alg :: [a] -> List a
list2alg [] = Nil
list2alg (x:xs) = Cons x (list2alg xs)

--13

divisionSegura :: Float -> Float -> Maybe Float
divisionSegura _ 0 = Nothing
divisionSegura a1 a2 = Just (a1 / a2)

--14

join :: (a -> c) -> (b -> d) -> Either a b -> Either c d
join f _ (Left a) = Left (f a)
join _ f (Right a) = Right (f a) 

--15

type Resultado a = Either a String

--16

llamarDiv :: Float -> Float -> Resultado Float
llamarDiv a1 a2 = transformar (divisionSegura a1 a2)
    where
        transformar (Just r) = Left r
        transformar Nothing = Right "Division por cero"
