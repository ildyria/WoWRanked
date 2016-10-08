#pragma once

#include <vector>
#include "Rank.h"

class Progress {
    short rank = 23;
    short stars = 0;
    short stars_max = 0;
    short max_rank = 23;
    std::vector<Rank> &ranks;

public:
    Progress(std::vector<Rank>& r)  : rank(23), stars(0), stars_max(1), max_rank(23), ranks(r) {};
    ~Progress(){};

    void set_ranks(std::vector<Rank>& r)
    {
        ranks = r;
    }

    void init() {
        rank = 23;
        stars = 0;
        stars_max = 1;
        max_rank = 23;
    }

    void level_up() {
        rank --;
        stars = 1;
        if(rank < max_rank)
        {
            max_rank = rank;
        }
        stars_max = ranks[rank].get_stars();
    }

    void level_down () {
        rank ++;
        stars_max = ranks[rank].get_stars();
        stars = stars_max - (short) 1;
    }

    inline void win() {
        stars ++;
        if(stars == stars_max && rank > 1)
        {
            level_up();
        }
    }

    inline void lose () {
        stars --;
        if(stars < 0){
            if(ranks[rank].is_irrevocable())
            {
                stars = 0;
            }
            else
            {
                level_down();
            }
        }
    }

    inline bool is_rank1() {
        return rank == 1;
    }

    inline short get_max_rank() {
        return max_rank;
    }

    inline short get_rank() {
        return rank;
    }

    inline short get_star() {
        return stars;
    }

    inline short get_max_stars() {
        return stars_max;
    }
};
