module Board where

type Tile = Maybe Int

type Board = [[Tile]]

type Pos = (Int, Int)

type Size = Int

--returns tile at given position
getTile :: Board -> Pos -> Tile
getTile board (pos1, pos2) = board !! pos1 !! pos2

--checks if position matches the size of the board
allowedPos :: Int -> Pos -> Bool
allowedPos size (pos1, pos2) = pos1 >= 0 && pos2 >= 0 && pos1 < size && pos2 < size

--returns the movements in the four direction around a
-- given position, generating them, but without any constraints
generatePositions :: Pos -> [Pos]
generatePositions (pos1, pos2) =
  [(pos1 - 1, pos2), (pos1, pos2 -1), (pos1 + 1, pos2), (pos1, pos2 + 1)]

--returns possible mouvements of a tile
getPossiblePositions :: Pos -> Int -> [Pos]
getPossiblePositions pos size =
  filter (allowedPos size) (generatePositions pos)

-- swaps tiles at pos1 and pos2 on board
flipTiles :: Board -> Pos -> Pos -> Board
flipTiles board pos1 pos2 = setMatrixValue pos1 (setMatrixValue pos2 board tile1) tile2
  where
    tile1 = getTile board pos1
    tile2 = getTile board pos2

-- get a list of Boards with possible movements of a certain tile
neighbours :: Pos -> Board -> [Board]
neighbours pos board = map (flipTiles board pos) positions
  where
    len = length board
    positions = getPossiblePositions pos len

-- find empty tile
findEmpty :: Board -> Pos
findEmpty board = head [(i, j) | i <- [0 .. size - 1], j <- [0 .. size - 1], isNothing (getTile board (i, j))]
  where
    size = length board

isNothing :: Tile -> Bool
isNothing tile = tile == Nothing

-- check if board is in final state
isFinal :: Board -> Bool
isFinal board = isFinal' len 0 False flatBoard
  where
    flatBoard = concat board
    len = length flatBoard
    -- len, position, isNothing saw, List of tiles
    -- final should be on first position
    isFinal' :: Int -> Int -> Bool -> [Tile] -> Bool
    isFinal' n _ isNothingSaw [] = n == 0 && isNothingSaw
    isFinal' n pos isNothingSaw (Nothing : xs)
      | n > 1 && null xs || isNothingSaw = False
      | otherwise = isFinal' (n -1) pos True xs
    isFinal' n pos isNothingSaw (Just a : xs)
      | n > 0 && isNothingSaw && pos + 1 == a =
        isFinal' (n -1) (pos + 1) isNothingSaw xs
      | otherwise = False

-- get twin board
twin :: Board -> Board
twin board
  | len <= 1 = board
  | tile1 == Nothing || tile2 == Nothing = flipTiles board (1, 0) (1, 1)
  | otherwise = flipTiles board (0, 0) (0, 1)
  where
    len = length board
    tile1 = getTile board (0, 0)
    tile2 = getTile board (0, 1)

-- given a tile and len, return its position
tilePosition :: Tile -> Size -> Pos
tilePosition Nothing _ = (0, 0)
tilePosition (Just tile) size = (row, col)
  where
    row = fromIntegral ((tile - 1) `quot` size)
    col = fromIntegral ((tile - 1) `mod` size)

-- get manhattan distance of one tile to its final position
manhattanTile :: Tile -> Size -> Pos -> Int
manhattanTile Nothing _ _ = 0
manhattanTile tile size (i, j) = abs (i - finalI) + abs (j - finalJ)
  where
    (finalI, finalJ) = tilePosition tile size

-- get manhattan distance of the whole board
manhattanBoard :: Board -> Int
manhattanBoard board = sum distBoard
  where
    size = length board
    distBoard = [manhattanTile (getTile board (i, j)) size (i, j) | i <- [0 .. size - 1], j <- [0 .. size - 1]]

notOnPlaceTiles :: Board -> Int
notOnPlaceTiles board = notOnPlaceTiles' 0 board

-- heuristic two, number of tiles not on place
notOnPlaceTiles' :: Int -> Board -> Int
notOnPlaceTiles' _ [] = 0
notOnPlaceTiles' row board@(row1 : others) = notOnPlaceTilesRow (row, 0) size row1 + notOnPlaceTiles' (row + 1) others
  where
    size = length board
    notOnPlaceTilesRow :: Pos -> Size -> [Tile] -> Int
    notOnPlaceTilesRow _ _ [] = 0
    notOnPlaceTilesRow (r, c) size (tile : others)
      | (tilePosition tile size) == (r, c) = 1 + notOnPlaceTilesRow (r, c + 1) size others
      | otherwise = notOnPlaceTilesRow (r, c + 1) size others

-- Takes the position of the element to change, the list and a function applied to the element we
-- want to change
setRow :: Int -> [a] -> (a -> a) -> [a]
setRow _ [] _ = []
setRow 0 (x : xs) f = f x : xs
setRow pos (x : xs) f = x : setRow (pos - 1) xs f

setRowValue :: Int -> [a] -> a -> [a]
setRowValue pos xs val = setRow pos xs (const val)

setMatrix :: Pos -> [[a]] -> (a -> a) -> [[a]]
setMatrix (pos1, pos2) matrix f = setRow pos1 matrix (\row -> setRow pos2 row f)

setMatrixValue :: Pos -> [[a]] -> a -> [[a]]
setMatrixValue pos matrix val = setMatrix pos matrix (const val)

-- printing functions for Board

printBoardRow :: [Tile] -> String
printBoardRow [] = ""
printBoardRow (x : xs) = printTile x ++ " " ++ printBoardRow xs

printBoard :: Board -> String
printBoard [] = ""
printBoard (x : xs) = (printBoardRow x) ++ "\n" ++ printBoard xs

printTile :: Tile -> String
printTile (Just a) = show a
printTile Nothing = "X"

printBoardList :: [Board] -> String
printBoardList [] = ""
printBoardList (x : xs) = (printBoard x) ++ "\n" ++ printBoardList xs