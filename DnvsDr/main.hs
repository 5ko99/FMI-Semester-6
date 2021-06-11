f :: Integer -> Integer
f x = if x == 0 then f (g x (f x)) else 0

g :: Integer -> Integer -> Integer
g x y = if x == 0 then 0 else g (f x) y

-- for every x from N = 0
-- see cpp file for value semantic
func :: Integer -> Integer
func x = g x (f x)

main :: IO ()
main = do
  putStrLn "Input x"
  line <- getLine
  let x = read line :: Integer
  print (func x)