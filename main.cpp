#include <iostream>
#include <vector>
#include <ctime>

class catchWrongThing : public std::exception {
 public:
  const char* what() const noexcept override { 
    return "Caught wrong thing!";
  }
};

class Fishing {
 private:
  std::vector<bool> pitch;
  int choice = 0;

 public:
  Fishing() {
    pitch.resize(9);

    for (int i = 0; i < pitch.size(); i++) {
      pitch[i] = true;
    }
  }

  inline void setPitch() {
    bool buffer[3]{0, 0, 0};
    for (int i = 0; i < 3; i++) {
      int randomIndex = std::rand() % pitch.size();
      for (int i = 0; i < 3; i++) {
        if (buffer[i] == randomIndex) throw std::exception();
      }

      try {
        pitch[randomIndex] = false;
        buffer[i] = randomIndex;
      } catch (const std::exception& x) {
        std::cerr << "Wrong index!";
      }
    }
  }

  inline void setFish() {
    std::cout << "Enter the number(0-9): ";
    std::cin >> choice;

    if (pitch[choice] == false) throw catchWrongThing();

    try {
      std::cout << "You win!" << std::endl;
    } catch (const catchWrongThing& x) {
      std::cout << "Exception: " << x.what() << std::endl;
    }
  }
};

int main() {
  srand(std::time(nullptr));
  Fishing pitch;
  pitch.setPitch();
  pitch.setFish();
}