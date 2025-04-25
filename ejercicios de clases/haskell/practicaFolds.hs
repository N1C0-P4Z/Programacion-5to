data Nat = Zero | Succ Nat

foldnat :: (r -> r) -> r -> Nat -> r
foldnat f b Zero = b
foldnat f b (Succ n) = f (foldnat f b n)

valorConFold :: Nat -> Int
valorConFold = foldnat (1 +) 0

data List a = Nil | Cons a (List a)

foldlist :: (a -> r -> r) -> r -> List a -> r
foldlist f b Nil = b
foldlist f b (Cons a l) = f a (foldlist f b l)

-- 2.8 ( sumar con foldlist)

sumarFold :: List Int -> Int
sumarFold Nil = 0
sumarFold (Cons a l) = foldlist (+) 0 (Cons a l)

data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr

foldExpr :: (r -> r -> r) -> (r -> r -> r) -> (Int -> r) -> Expr -> r
foldExpr s r i (Literal a) = i a
foldExpr s r i (Suma a b) = s (foldExpr s r i a) (foldExpr s r i b)
foldExpr s r i (Resta a b) = r (foldExpr s r i a) (foldExpr s r i b)

evaluarExpr :: Expr -> Int
evaluarExpr = foldExpr (+) (-) id
