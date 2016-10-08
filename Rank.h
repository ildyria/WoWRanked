#pragma once


class Rank {

    short stars = 2;
    bool irrevocable = false;

public:
    Rank() : stars(2), irrevocable(false) {};

    ~Rank(){};

    inline void set_irrevocable()
    {
        irrevocable = true;
    }

    inline bool is_irrevocable()
    {
        return irrevocable;
    }

    inline void set_stars(short s)
    {
        stars = s;
    }

    inline short get_stars(){
        return stars;
    }

};
