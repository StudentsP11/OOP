#ifndef PETS_H
#define PETS_H

#include <iostream>

class Pet {
public:
    explicit Pet(uint16_t volume)
        : volume_{volume}
    {}
    virtual void grow() = 0;
    virtual ~Pet() = default;
protected:
    uint16_t volume_;
};

class Dog : public Pet {
public:
    Dog(uint16_t volume, uint16_t fur_length)
        : Pet(volume), fur_length_(fur_length)
    {}

    void grow() final {
        volume_ *= 2;
        fur_length_ += 1;
    }
private:
    uint16_t fur_length_;
};

class Turtle : public Pet {
public:
    Turtle(uint16_t volume,uint16_t shell_thickness)
            : Pet(volume), shell_thickness_{shell_thickness}
    {}

    void grow() final {
        volume_ += 1;
        shell_thickness_ += 1;
    }
public:
    uint16_t shell_thickness_;
};


#endif