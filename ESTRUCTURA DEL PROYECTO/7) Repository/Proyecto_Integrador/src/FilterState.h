/**********************************************************************

  FILE        : FilterState.h
  DATE        : 26/04/2019
  DESCRIPTION : Set and reset main tick
  PROJECT     : DSE: 2.2.6 Maquina de estados

 **********************************************************************/
#include "hal_data.h"
#include "mainTick.h"

#define LOW 1
#define HIGH 0

typedef struct btnFilter
{
    int timer;
    int stateMachine;
    bool Trigger;

} filterBtn;

void FilterState(ioport_level_t Input, filterBtn *btnFilter);

void FilterState(ioport_level_t Input, filterBtn *btnFilter)
{
    switch(btnFilter->stateMachine)
    {
        case 0 :
            btnFilter-> Trigger = false;

            if (Input == HIGH)
            {
                btnFilter->stateMachine = 1;
            }
            break;

        case 1:
            btnFilter->timer++;
            if(Input == HIGH){
                if(btnFilter->timer > 5)
                {
                    btnFilter->stateMachine = 2;
                    btnFilter->timer = 0;
                    //btnFilter->Trigger = true;
                }
                else
                    btnFilter->stateMachine = 0;
            }
            break;
        case 2:
            btnFilter->Trigger = true;
            btnFilter->stateMachine = 3;
            break;
        case 3:
            btnFilter->Trigger = false;
            if (Input ==LOW)
            {
                btnFilter->stateMachine = 0;
            }
            break;
    }
}
