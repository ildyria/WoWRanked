#include <iostream>
#include <stdio.h>
#include <string>
#include "omp.h"
#include <vector>
#include "includes/typedef.h"
#include "tools/timer.h"
#include "tools/random.h"
#include "Rank.h"
#include "Progress.h"

int main(int argc, char const *argv[])
{
	printf("\n \t \tIf it compiles then it works !\n");
	printf("\t But remember, all code is guilty until proven innocent !\n");
	printf("\t \tWhen in doubt, use Brute force ! - Ken Thompson\n \n");

    unsigned long simulations_num = 1000000;
    unsigned long max_games = 200;

	prog_options options = read_args(argc, argv);

	Timer t = Timer();
	Random::I(0);
	int i;
	std::vector<Rank> levels = std::vector<Rank>(24);
	levels[0].set_stars(0);
	levels[1].set_stars(1);
	for (i = 2; i < 6; ++i) {
		levels[i].set_stars(5);
	}
	for (i = 6; i < 11; ++i) {
		levels[i].set_stars(4);
	}
	for (i = 11; i < 16; ++i) {
		levels[i].set_stars(3);
	}
	levels[23].set_stars(1);

	levels[1].set_irrevocable();
	levels[12].set_irrevocable();
	levels[15].set_irrevocable();
	for (i = 17; i < 24; ++i) {
		levels[i].set_irrevocable();
	}


    std::vector<Progress> progrsses = std::vector<Progress>(options.num_proc_to_use, Progress(levels));

    std::vector<unsigned long> results = std::vector<unsigned long>(24,0);

    for (unsigned long j = 0; j < simulations_num; ++j) {
        unsigned long k = 0;
        Progress* p = &progrsses[omp_get_thread_num()];
        p->init();
        while (k < max_games && !p->is_rank1()) {

            uint64_t r = Random::I()->get();
            if ((r & 1) != 0)
            {
                p->win();
//                printf("Win !\n");
//                printf("%2i (%i / %i) \n",p->get_rank(),p->get_star(),p->get_max_stars());
            }
            else
            {
                p->lose();
//                printf("Lose !\n");
//                printf("%2i (%i / %i) \n",p->get_rank(),p->get_star(),p->get_max_stars());
            }
            k++;
        }
        printf("%2i (%i / %i) \n",p->get_rank(),p->get_star(),p->get_max_stars());
        results[p->get_max_rank()]++;
    }

    unsigned long sim_num = 0;
    for (i = 0; i < 24; ++i) {
        sim_num += results[i];
        printf("rank %2i : %6li (%3li%%) - %7li (%3li%%)\n",i,results[i],results[i]/10000,sim_num,sim_num/10000);
    }


	t.stop();
	printf("done in : %.3lf ms\n", t.resultmus()/1000000.0);
	printf("------------------------------------------------------------\n");

	return 0;
}