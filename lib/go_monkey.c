#include "go_monkey.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *     http://library.gnome.org/devel/gobject/2.21/gobject-Type-Information.html#G-DEFINE-TYPE--CAPS
 A convenience macro for type implementations, which declares a class
 initialization function, an instance initialization function (see GTypeInfo
 for information about these) and a static variable named t_n_parent_class
 pointing to the parent class. Furthermore, it defines a *_get_type()
 function. See G_DEFINE_TYPE_EXTENDED() for an example.
 */
G_DEFINE_TYPE (NatureMonkey, nature_monkey, NATURE_ANIMAL_TYPE);

/* Define the private structure in the .c file */
#define NATURE_MONKEY_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), NATURE_MONKEY_TYPE, NatureMonkeyPrivate))

struct _NatureMonkeyPrivate
{
   char *place;
   char *kind;
};

static GObject*
_nature_monkey_constructor(GType type, guint n_par, GObjectConstructParam *params)
{
   printf("%s - start\n", __func__);

   /*
    ** in this part of the code we have control over:
    ** - the type of object the user intends to create
    ** - the number of arguments the user has passed to g_object_new
    ** - the spec and the value each argument has
    **/
   guint i;
   for (i = 0; i < n_par; i++) {
        /* we will print the the properties' names and if it's
         *        * an integer we'll print it's value
         *              */
        g_print ("%s", params[i].pspec->name);
        if (G_VALUE_HOLDS_INT (params[i].value))
           g_print(": %d", g_value_get_int (params[i].value));
        g_print ("\n");
   }

  /*chain up to parent constructor*/
   GObject *obj;

   NatureMonkeyClass *klass;
   GObjectClass *parent_class;
   klass = NATURE_MONKEY_CLASS(g_type_class_peek (NATURE_MONKEY_TYPE));
   parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(klass));

   printf("explicit call for monkey parent constructor - start\n");
   obj = parent_class->constructor(type, n_par, params);
   printf("explixit call for monkey parent constructor - end\n");

   /*do whatever we want in this constructor*/

   printf("%s - end\n", __func__);
   return obj;
}

static void
_monkey_cry (NatureAnimal *self, gchar *msg)
{
   printf("%s - %s\n",__func__,  msg );
   (void) self;
}

static void
_nature_monkey_finalize(NatureMonkey *self)
{
   printf("%s\n", __func__);

   NatureMonkeyPrivate *priv;
   priv = NATURE_MONKEY_GET_PRIVATE(self);

   //printf("%s :: %s\n", __func__, priv->kind);
   free(priv->kind);
   priv->kind = NULL;
   free(priv->place);
   priv->place = NULL;

   /*chain up to parent class*/
   NatureMonkeyClass *klass;
   GObjectClass *parent_class;
   klass = NATURE_MONKEY_GET_CLASS(self);
   parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(klass));
   parent_class->finalize(G_OBJECT(self));

}

static void
nature_monkey_class_init (NatureMonkeyClass *klass)
{
   GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
   gobject_class->constructor = _nature_monkey_constructor;
   gobject_class->finalize = (GObjectFinalizeFunc)_nature_monkey_finalize;

   g_type_class_add_private (klass, sizeof (NatureMonkeyPrivate));
   /* Setup the default handler for virtual method */
   NATURE_ANIMAL_CLASS(klass)->cry = _monkey_cry;
}

static void
nature_monkey_init (NatureMonkey *self)
{
   printf("%s - start\n", __func__);
   /* Initialize all public and private members to reasonable default values. */
   /* Initialize public fields */

   self->monkey_public = 0;
   printf("  initializing monkey_public to \"%d\"\n", self->monkey_public);

   /* Initialize private fields */
   NatureMonkeyPrivate *priv;
   self->private_data = priv = NATURE_MONKEY_GET_PRIVATE(self);
   priv->kind = strdup("Default");
   priv->place = strdup("Default");

   printf("  initializing private kind to \"%s\"\n", priv->kind);
   printf("  initializing private place to \"%s\"\n", priv->place);

   /* If you need specific construction properties to complete initialization,
    * delay initialization completion until the property is set.
    */
   printf("%s - end\n", __func__);
}

NatureAnimal*
nature_monkey_new(const char *name, int age)
{
   return NATURE_ANIMAL(g_object_new(NATURE_MONKEY_TYPE,
            "name", name,
            "age", age, NULL));
}

void
nature_monkey_set_private(NatureAnimal *_self ,char *_kind, char *_place)
{
   /* First test that 'self' is of the correct type */

   NatureMonkey *self = NATURE_MONKEY(_self);
   g_return_if_fail (NATURE_IS_MONKEY(self));

   NatureMonkeyPrivate *priv;
   priv = NATURE_MONKEY_GET_PRIVATE(self);

   printf("%s :: \n", __func__);
   free(priv->kind);
   priv->kind = strdup(_kind);

   free(priv->place);
   priv->place = strdup(_place);
}

void
nature_monkey_print_private(NatureAnimal *_self)
{
   NatureMonkey *self = NATURE_MONKEY(_self);
   g_return_if_fail (NATURE_IS_MONKEY(self));

   NatureMonkeyPrivate *priv;
   priv = NATURE_MONKEY_GET_PRIVATE(self);

   printf("%s :: %s; %s\n", __func__,
         priv->kind, priv->place);
}

