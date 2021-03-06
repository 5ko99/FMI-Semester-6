f :: Integer -> Integer
f x = if x == 0 then f (g x (f x)) else 0

g :: Integer -> Integer -> Integer
g x y = if x == 0 then 0 else g (f x) y

-- for every x from N = 0
-- see cpp file for value semantic
func :: Integer -> Integer
func x = g x (f x)

f1 :: Integer -> Integer -> Integer
f1 x k = if x `mod` k == 0 then x `div` k else f1 (f1 (k * x - 1) k) k

main :: IO ()
main = do
  putStrLn "Input x"
  line <- getLine
  let x = read line :: Integer
  print (func x)