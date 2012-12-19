#include "go_nature.h"
#include "go_monkey.h"
#include "go_human.h"
#include "go_digital.h"
#include <stdio.h>

#ifdef GOIS
#include <girepository.h>
#endif

int
main (int argc, char *argv[])
{
 g_type_init();
#ifdef GOIS
   GOptionContext *ctx;
   GError *error = NULL;

   ctx = g_option_context_new (NULL);
   g_option_context_add_group (ctx, g_irepository_get_option_group ());

   if (!g_option_context_parse (ctx, &argc, &argv, &error))
      {
         g_print ("swimmer: %s\n", error->message);
        // exit(1);
       }
#endif

   /*
    * Prior to any use of the type system, g_type_init() has to be called
    * to initialize the type system and assorted other code portions
    * (such as the various fundamental type implementations or the signal
    * system).
    */
   /* Create our object */
   NatureAnimal *an = nature_animal_new("Animal", 12);
   //SwimmerSw *sw = g_object_new(SWIMMER_TYPE, NULL);
   an->age += 1;
   g_print("incremented animal->age:  %d\n", an->age);
   /* Call object method */
   nature_animal_eat(an, "helowrld");
   nature_animal_cry(an, "test");
   my_int num = 110183;
   nature_animal_myint(an, num);
   nature_animal_uint(an, num*2);
   nature_animal_get_data(an);
   g_object_unref(an);
//   nature_animal_do_action(sw);

   printf("\n\n");
   NatureAnimal *m = nature_monkey_new("Monkey", 10);
   nature_animal_eat(m, "eat_monkey");
   nature_animal_cry(m, "cry monkey");

   nature_animal_get_data(m);
   m->age += 3;
   nature_animal_get_data(m);
//   nature_animal_do_action(m);
   nature_monkey_print_private(m);
   nature_monkey_set_private(m, "gorilla", "afrika");
   nature_monkey_print_private(m);
   g_object_unref(m);

   printf("\n");
   NatureAnimal *h = mankind_human_new("Jack", 30);
   nature_animal_eat(h, "eat_human");
   nature_animal_cry(h, "cry human");
   nature_animal_get_data(h);
   int r =9;
   int *arr;
   nature_animal_pint(h, &r, &arr);
   printf("r = %d\n", r);
   printf("arr[0] = %d\n", arr[0]);
   printf("arr[1] = %d\n", arr[1]);

   mankind_human_print_private(h);

/*
   printf("\n");
   DigitalComp *dc = digital_comp_new("Jack", 30);

   digital_comp_compute(dc, "comp compute");
   digital_comp_reboot(dc, "comp reboot");
   digital_comp_halt(dc);
*/


   (void) argc;
   (void) argv;
   return 0;
}
