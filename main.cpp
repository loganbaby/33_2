#include <iostream>
#include <vector>
#include <ctime>

class catchWrongBoot : public std::exception {
 public:
  const char* what() const noexcept override { 
    return "Exception: Wrong boot\n";
  }
};

class catchWrongIndex : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Exception: Wrong random index\n";
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
        try {
          if (buffer[i] == randomIndex) throw catchWrongIndex();
          pitch[randomIndex] = false;
          buffer[i] = randomIndex;
        } catch (const std::exception& x) {
          std::cerr << x.what();
        }
      }
    }
  }

  inline void setFish() {
    std::cout << "Enter the number(0-9): ";
    std::cin >> choice;
    try {
      if (pitch[choice] == false) throw catchWrongBoot();
      std::cout << "You win!" << std::endl;
    } catch (const catchWrongBoot& x) {
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