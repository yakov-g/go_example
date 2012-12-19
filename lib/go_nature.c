#include "go_nature.h"
#include <stdlib.h>
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
//G_DEFINE_TYPE (NatureAnimal, nature_animal, G_TYPE_OBJECT);


/* Define the private structure in the .c file */
/*
#define NATURE_ANIMAL_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), NATURE_ANIMAL_TYPE, NatureAnimalPrivate))


struct _NatureAnimalPrivate
{
   int hsize;
   char *msg;
};
*/


enum{
     NATURE_ANIMAL_CONSTRUCT_NAME = 1,
     NATURE_ANIMAL_CONSTRUCT_AGE,
};

static GObject*
_nature_animal_constructor(GType type, guint n_par, GObjectConstructParam *params)
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
         ** an integer we'll print it's value
         **/
        g_print ("%s", params[i].pspec->name);
        if (G_VALUE_HOLDS_INT (params[i].value))
           g_print(": %d", g_value_get_int (params[i].value));
        g_print ("\n");
   }

   GObject *obj;
   NatureAnimalClass *klass;
   GObjectClass *parent_class;
   klass = NATURE_ANIMAL_CLASS(g_type_class_peek (NATURE_ANIMAL_TYPE));
   parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(klass));
   printf("call for animal parent(gobject constr) constructor - start\n");
   /*here g_object_constructor is invoked.
    * it creates all instances and
    * invokes all init instance functions
    * and set properties functions*/
   obj = parent_class->constructor(type, n_par, params);
   printf("call for animal parent(gobject constr) constructor - end\n");

   /*do whatever we want in this constructor*/

   /*so now instance is created.
     we can manually  assign values without using property set
     but in this case we need to look for our parameters in loop in the beginning
     */
#if (0)
   NatureAnimal *na = NATURE_ANIMAL(obj);
   printf("constr: age: %d\n", na->age);
   na->age = 45;
   printf("constr: age: %d\n", na->age);
#endif

   printf("%s - end\n", __func__);
   return obj;
}

/* Object virtual method default action (can be overridden) */
static void
_animal_eat (NatureAnimal *self, gchar *msg)
{
   printf("%s - %s\n",__func__,  msg );
   (void) self;
}

static void
_animal_cry (NatureAnimal *self, gchar *msg)
{
   printf("%s - %s\n",__func__,  msg );
   (void) self;
}

static void
_animal_myint (NatureAnimal *self, my_int n)
{
   printf("%s - %d\n",__func__,  n );
   (void) self;
}

static void
_animal_usualint (NatureAnimal *self, int n)
{
   printf("%s - %d\n",__func__,  n );
   (void) self;
}


static void
_animal_pint (NatureAnimal *self, int *n, int **a)
{

     printf("%s \n",__func__);
  //   printf("%s - %d\n",__func__,  *n );
 //  *n=110183;
   int *p;
   p = (int*)malloc(sizeof(int)*2);
   p[0] = 11;
   p[1] = 1101;
   *a= p;
   (void) self;
}


static void
_get_data(NatureAnimal *self)
{
   printf("%s :: ",__func__ );
   printf("Name: %s; Age: %d;\n", self->name, self->age);
   (void) self;
}

static void
_nature_animal_set_property(GObject * object,
                                      guint prop_id,
                                      const GValue *value,
                                      GParamSpec *pspec)
{

   printf("%s - begin\n", __func__);

   NatureAnimal *self;
   self = NATURE_ANIMAL(object);
   switch (prop_id)
   {
      case NATURE_ANIMAL_CONSTRUCT_AGE:
         self->age = g_value_get_int (value);
         printf("  setting property age: %d\n", self->age);
         break;
      case NATURE_ANIMAL_CONSTRUCT_NAME:
         free(self->name);
         self->name = strdup(g_value_get_string(value));
         printf("  setting property name: %s\n", self->name);
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
         break;
   }
   printf("%s - end\n", __func__);
}

static void
_nature_animal_get_property(GObject * object,
                                      guint prop_id,
                                      GValue *value,
                                      GParamSpec *pspec)
{
   printf("%s - begin\n", __func__);
   NatureAnimal *self;
   self = NATURE_ANIMAL(object);
   switch (prop_id)
   {
      case NATURE_ANIMAL_CONSTRUCT_AGE:
         g_value_set_int(value, self->age);
         break;
      case NATURE_ANIMAL_CONSTRUCT_NAME:
         g_value_set_string(value, self->name);
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
         break;
   }
   printf("%s - end\n", __func__);
}

static void
_nature_animal_finalize(NatureAnimal *self)
{
   printf("%s\n", __func__);
   self->age = 0;
   free(self->name);
}

static void
nature_animal_class_init (NatureAnimalClass *klass)
{
   GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
   printf("%s\n", __func__);

   gobject_class->constructor = _nature_animal_constructor;
   gobject_class->set_property = _nature_animal_set_property;
   gobject_class->get_property = _nature_animal_get_property;
   //Instance finalization function
   gobject_class->finalize = (GObjectFinalizeFunc)_nature_animal_finalize;

   GParamSpec *pspec;

   pspec = g_param_spec_string("name",/*id*/
                               "construct prop",
                               "set name",
                               "NoName", /*default value*/
                               G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
   g_object_class_install_property(gobject_class,
                                   NATURE_ANIMAL_CONSTRUCT_NAME,
                                   pspec);

   pspec = g_param_spec_int("age",
                            "animals age",
                            "set age",
                            0,
                            G_MAXINT,
                            0,
                            G_PARAM_READWRITE | G_PARAM_CONSTRUCT);

   g_object_class_install_property(gobject_class,
                                   NATURE_ANIMAL_CONSTRUCT_AGE,
                                   pspec);
//for private data
/*
/A similar alternative, available since Glib version 2.4, is to define a private structure in the .c file, declare it
as a private structure in class_init using g_type_class_add_private and declare a macro to allow
convenient access to this structure. A private structure will then be attached to each newly created object
by the GObject system. You dont need to free or allocate the private structure, only the objects or pointers
that it may contain.
*/
//
  // g_type_class_add_private (klass, sizeof (NatureAnimalPrivate));
   /* Setup the default handler for virtual method */
   klass->eat = _animal_eat;
   klass->cry = _animal_cry;
   klass->myint = _animal_myint;
   klass->usualint = _animal_usualint;
   klass->p_to_int = _animal_pint;
   klass->get_data = _get_data;
}


static void
nature_animal_init (NatureAnimal *self)
{
   printf("%s - start\n", __func__);
   /* Initialize all public and private members to reasonable default values. */
   /* Initialize public fields */
   self->age = 0;
   self->name = NULL;
// strncpy(self->name, "NoName", sizeof(self->name)-1);
   printf("  initializing public age to \"%d\"\n", self->age);
   printf("  initializing public name to \"%s\"\n", self->name);


   /* Initialize private fields */
   /*
   NatureAnimalPrivate *priv;
   self->priv = priv = NATURE_ANIMAL_GET_PRIVATE(self);
   priv->hsize = 42;
   g_print("  init'd private variable priv->hsize to %d\n", priv->hsize);


   /* If you need specific construction properties to complete initialization,
    * delay initialization completion until the property is set. 
    */

   printf("%s - end\n", __func__);
}

NatureAnimal*
nature_animal_new(const char *name, int age)
{
   return NATURE_ANIMAL(g_object_new(NATURE_ANIMAL_TYPE,
                        "name", name,
                        "age", age, NULL));
}

/* Object non-virtual method */
void nature_animal_poop(NatureAnimal *self)
{
   printf("here\n");
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("poop\n");
}

/* Object virtual method call - performs the override */
void nature_animal_eat (NatureAnimal *self, gchar *msg)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("%s :: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->eat(self, msg);
}

void nature_animal_cry (NatureAnimal *self, gchar *msg)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("%s :: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->cry(self, msg);
}

void nature_animal_myint (NatureAnimal *self, my_int n)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("%s:: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->myint(self, n);
}

/**
 * nature_animal_uint:
 * @self: object instance
 * @nn: some parameter
 *
 * Introspecting usual integer type
 */

void nature_animal_uint (NatureAnimal *self, int nn)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("%s:: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->usualint(self, nn);
}

void nature_animal_pint (NatureAnimal *self, int *n, int **a)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL (self));
   printf("%s:: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->p_to_int(self, n, a);
}

void nature_animal_get_data(NatureAnimal *self)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (NATURE_IS_ANIMAL(self));
   printf("%s :: ", __func__);
   NATURE_ANIMAL_GET_CLASS (self)->get_data(self);
}
/*
void nature_animal_do_action(NatureAnimal *self)
{
   g_return_if_fail(NATURE_IS_ANIMAL(self));
   printf("%s :: %d\n", __func__, self->priv->hsize);
}
*/
//#if(0)
static void nature_animal_instance_init(
      GTypeInstance *instance, gpointer g_class)
{
   NatureAnimal *self = (NatureAnimal *) instance;
   nature_animal_init(self);
   (void) g_class;
}

GType
nature_animal_get_type(void)
{
   static GType type = 0;

   if (type == 0) {

        static const GTypeInfo info = {
             sizeof (NatureAnimalClass),
             (GBaseInitFunc)NULL,           /* base_init */
             (GBaseFinalizeFunc)NULL,           /* base_finalize */
             (GClassInitFunc) nature_animal_class_init,
             (GClassFinalizeFunc)NULL,           /* class_finalize */
             NULL,           /* class_data */
             sizeof (NatureAnimal),
             0,              /* n_preallocs */
             /*
              * Instance(object) initialization func.
              * All chain of instance_init funcs
              * Is invoked by g_object_constructor().
              * which must be invoked by last constructor in chain
              * */
             (GInstanceInitFunc)nature_animal_instance_init,/* instance_init */
             NULL
        };

        type = g_type_register_static (G_TYPE_OBJECT, "NatureAnimal", &info, 0);
   }

   return type;
}

//#endif
