import Board
import Control.Exception (evaluate)
import Test.Hspec

--import Test.QuickCheck

main :: IO ()
main = hspec $ do
  describe "Test of isFinal" $ do
    it "in order, nothing in end" $
      isFinal board1 `shouldBe` False
    it
      "in order, nothing first"
      $ isFinal
        board2
        `shouldBe` True
    it
      "in order, nothing in middle"
      $ isFinal
        board3
        `shouldBe` False
    it "not in order" $
      isFinal board4 `shouldBe` False
    it "two nothings" $
      isFinal board5 `shouldBe` False
    it "First and last are nothing" $
      isFinal board5 `shouldBe` False
  describe "test notOnPlace" $ do
    it "all of them not on place" $
      notOnPlaceTiles board1 `shouldBe` 9
    it "all of them on place" $
      notOnPlaceTiles board2 `shouldBe` 0

board1 :: Board
board1 = [[Just 1, Just 2, Just 3], [Just 4, Just 5, Just 6], [Just 7, Just 8, Nothing]]

board2 :: Board
board2 = [[Nothing, Just 1, Just 2], [Just 3, Just 4, Just 5], [Just 6, Just 7, Just 8]]

board3 :: Board
board3 = [[Just 1, Just 2, Just 3], [Just 4, Just 5, Nothing], [Just 6, Just 7, Just 8]]

board4 :: Board
board4 = [[Just 1, Just 2, Just 3], [Just 4, Just 5, Nothing], [Just 6, Just 8, Just 7]]

board5 :: Board
board5 = [[Just 1, Just 2, Just 3], [Just 4, Just 5, Just 6], [Nothing, Nothing, Just 7]]

board6 :: Board
board6 = [[Nothing, Just 1, Just 2], [Just 3, Just 4, Just 5], [Just 6, Just 7, Nothing]]