#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>
#include <vector>

#include "DSU.cpp"

class piece {
 private:
  sf::Sprite sprite;
  uint16_t index; //index in DSU
  uint8_t row; //row in puzzle matrix
  uint8_t col; //col in puzzle matrix
  uint16_t width;
  uint16_t height;

 public:
  piece(sf::Sprite sprite_, uint16_t index_, uint8_t row_, uint8_t col_, uint16_t width_, uint16_t height_) {
    sprite = sprite_;
    index = index_;
    row = row_;
    col = col_;
    width = width_;
    height = height_;
  };

  void setPosition(sf::Vector2f pos_);
  void setPosition(sf::Vector2i pos_);
  sf::Vector2f getPosition();
  void setTexture(sf::Texture texture_, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
  sf::Sprite draw();
  bool inPiece();
  uint16_t getIndex();
  sf::Vector2i getPositionInPuzzleMatrix();
  sf::Vector2i getSize();

};

class puzzle {
 private:
  uint8_t width; //count of pieces in one line
  uint8_t height; //count of pieces in one column
  std::vector<std::vector<piece>> pieces;
  sf::Texture pic;
  sf::Vector2f start_pos;
  DSU dsu_of_pieces;

 public:
  puzzle(uint8_t width_, uint8_t height_, sf::Texture& pic_, sf::Vector2f start_pos_): dsu_of_pieces(height_ * width_) {
    width = width_;
    height = height_;
    pic = pic_;
    start_pos = start_pos_;

    std::vector<piece> temp;
    for (int j = 0; j < width; j++) {
      sf::Sprite sprite_;
      piece piece_(sprite_, 0, 0, 0, 0, 0);
      temp.push_back(piece_);
    }
    for (int i = 0; i < height; i++) {
      pieces.push_back(temp);
    }

    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t piece_w = pic_.getSize().x / width;
    uint32_t piece_h = pic_.getSize().y / height;

    for (int i = 0; i < height; i++) {
      x = 0;
      for (int j = 0; j < width; j++) {
        sf::Sprite sprite_;
        sprite_.setTexture(pic_);
        sprite_.setTextureRect(sf::IntRect(x, y, piece_w, piece_h));
        piece piece_(sprite_, i * width + j, i, j, piece_w, piece_h);
        piece_.setPosition(sf::Vector2f(x + start_pos.x, y + start_pos.y));
        pieces[i][j] = piece_;
        x += piece_w;
      }
      y += piece_h;
    }
  }

  void draw(sf::RenderWindow& window);
  piece* isMouseInPiece();
  void shuffle();
  void setPosition(piece& piece_, sf::Vector2f pos_);
  std::vector<sf::Vector2i> getPiecesInUnion(piece& piece_);
  void connectPieces(piece& piece_);
};
