#include "go_digital.h"
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
//G_DEFINE_TYPE (DigitalComp, digital_comp, G_TYPE_OBJECT);


/* Define the private structure in the .c file */
/*
#define DIGITAL_COMP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DIGITAL_COMP_TYPEEE, DigitalCompPrivate))


struct _DigitalCompPrivate
{
   int hsize;
   char *msg;
};
*/


static GObject*
_digital_comp_constructor(GType type, guint n_par, GObjectConstructParam *params)
{
   printf("%s - start\n", __func__);

   GObject *obj;
   DigitalCompClass *klass;
   GObjectClass *parent_class;
   klass = DIGITAL_COMP_CLASS(g_type_class_peek (DIGITAL_COMP_TYPEEE));
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
   DigitalComp *na = DIGITAL_COMP(obj);
   printf("constr: age: %d\n", na->age);
   na->age = 45;
   printf("constr: age: %d\n", na->age);
#endif

   printf("%s - end\n", __func__);
   return obj;
}

/* Object virtual method default action (can be overridden) */
static void
_comp_compute(DigitalComp *self, gchar *msg)
{
   printf("%s - %s\n",__func__,  msg );
   (void) self;
}

static void
_comp_reboot(DigitalComp *self, gchar *msg)
{
   printf("%s - %s\n",__func__,  msg );
   (void) self;
}

static void
_comp_halt(DigitalComp *self)
{
   printf("%s :: ",__func__ );
   printf("Name: %s; Age: %d;\n", self->name, self->age);
   (void) self;
}

static void
_digital_comp_finalize(DigitalComp *self)
{
   printf("%s\n", __func__);
   self->age = 0;
   free(self->name);
}

static void
digital_comp_class_init (DigitalCompClass *klass)
{
   GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

   gobject_class->constructor = _digital_comp_constructor;
   gobject_class->finalize = (GObjectFinalizeFunc)_digital_comp_finalize;


//   g_type_class_add_private (klass, sizeof (DigitalCompPrivate));
   /* Setup the default handler for virtual method */
   klass->compute = _comp_compute;
   klass->reboot = _comp_reboot;
   klass->halt = _comp_halt;
}

static void
digital_comp_init (DigitalComp *self)
{
   printf("%s - start\n", __func__);
   /* Initialize all public and private members to reasonable default values. */
   /* Initialize public fields */
   self->age = 0;
   self->name = NULL;
// strncpy(self->name, "NoName", sizeof(self->name)-1);
   printf("  initializing public age to \"%d\"\n", self->age);
   printf("  initializing public name to \"%s\"\n", self->name);


   printf("%s - end\n", __func__);
}

DigitalComp*
digital_comp_new(const char *name, int age)
{
   return DIGITAL_COMP(g_object_new(DIGITAL_COMP_TYPEEE, NULL));
}

/* Object virtual method call - performs the override */
void digital_comp_compute (DigitalComp *self, gchar *msg)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (DIGITAL_IS_COMP (self));
   printf("%s :: ", __func__);
   DIGITAL_COMP_GET_CLASS (self)->compute(self, msg);
}

void digital_comp_reboot (DigitalComp *self, gchar *msg)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (DIGITAL_IS_COMP (self));
   printf("%s :: ", __func__);
   DIGITAL_COMP_GET_CLASS (self)->reboot(self, msg);
}

void digital_comp_halt(DigitalComp *self)
{
   /* First test that 'self' is of the correct type */
   g_return_if_fail (DIGITAL_IS_COMP(self));
   printf("%s :: ", __func__);
   DIGITAL_COMP_GET_CLASS (self)->halt(self);
}

//#if(0)
static void digital_comp_instance_init(
      GTypeInstance *instance, gpointer g_class)
{
   DigitalComp *self = (DigitalComp *) instance;
   digital_comp_init(self);
   (void) g_class;
}

GType
digital_comp_get_type(void)
{
   static GType type = 0;

   if (type == 0) {

        static const GTypeInfo info = {
             sizeof (DigitalCompClass),
             (GBaseInitFunc)NULL,           /* base_init */
             (GBaseFinalizeFunc)NULL,           /* base_finalize */
             (GClassInitFunc) digital_comp_class_init,
             (GClassFinalizeFunc)NULL,           /* class_finalize */
             NULL,           /* class_data */
             sizeof (DigitalComp),
             0,              /* n_preallocs */
             (GInstanceInitFunc)digital_comp_instance_init,/* instance_init */
             NULL
        };

        type = g_type_register_static (G_TYPE_OBJECT, "DigitalComp", &info, 0);
   }

   return type;
}

//#endif
