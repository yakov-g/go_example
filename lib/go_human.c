#include "go_human.h"
#include <stdio.h>
#include <string.h>
/*
 *     http://library.gnome.org/devel/gobject/2.21/gobject-Type-Information.html#G-DEFINE-TYPE--CAPS
 A convenience macro for type implementations, which declares a class
 initialization function, an instance initialization function (see GTypeInfo
 for information about these) and a static variable named t_n_parent_class
 pointing to the parent class. Furthermore, it defines a *_get_type()
 function. See G_DEFINE_TYPE_EXTENDED() for an example.
 */
G_DEFINE_TYPE (MankindHuman, mankind_human, NATURE_ANIMAL_TYPE);

/* Define the private structure in the .c file */
/*
Gets the private structure for a particular type. The private structure must have been registered in the class_init function with g_type_class_add_private() */
#define MANKIND_HUMAN_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), MANKIND_HUMAN_TYPE, MankindHumanPrivate))

struct _MankindHumanPrivate
{
   int height;
   int weight;
   char address[30];
};

static void
_human_cry (NatureAnimal *self, char *msg)
{
     printf("%s - %s\n",__func__,  msg );
     (void) self;
}

static void
mankind_human_class_init (MankindHumanClass *klass)
{
#if(0)
   G_OBJECT_CLASS(klass)->constructor = nature_animal_constructor;
#endif

   g_type_class_add_private (klass, sizeof (MankindHumanPrivate));
   /* Setup the default handler for virtual method */
   NATURE_ANIMAL_CLASS(klass)->cry = _human_cry;
}

//this function is used in G_DEFINE_TYPE to initialize instance
static void
mankind_human_init(MankindHuman *self)
{
   g_print("human_init() - init object\n");

   /* Initialize private fields */
   MankindHumanPrivate *priv;
   self->private_data = priv = MANKIND_HUMAN_GET_PRIVATE(self);

   priv->height = 180;
   priv->weight = 75;
   strncpy(priv->address, "New York", sizeof(priv->address)-1);

   printf("  initializing private height to \"%d\"\n", priv->height);
   printf("  initializing private weight to \"%d\"\n", priv->weight);
   printf("  initializing private address to \"%s\"\n", priv->address);

   /* If you need specific construction properties to complete initialization,
    * delay initialization completion until the property is set.
    */
}

NatureAnimal*
mankind_human_new(const char *name, int age)
{
   return NATURE_ANIMAL(g_object_new(MANKIND_HUMAN_TYPE,
                        "name", name,
                        "age", age, NULL));
}

void
mankind_human_print_private(NatureAnimal *_self)
{
     MankindHuman *self = MANKIND_HUMAN(_self);
     g_return_if_fail (MANKIND_IS_HUMAN(self));

     MankindHumanPrivate *priv;
     priv = MANKIND_HUMAN_GET_PRIVATE(self);

     printf("%s :: %s; %d; %d\n", __func__,
            priv->address, priv->height, priv->weight);
}


