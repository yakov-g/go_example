
#ifndef _GO_NATURE_H
#define _GO_NATURE_H

#include <glib-object.h>

typedef int my_int;


G_BEGIN_DECLS

#define NATURE_ANIMAL_TYPE nature_animal_get_type()

#define NATURE_ANIMAL(obj)   \
   (G_TYPE_CHECK_INSTANCE_CAST ((obj), NATURE_ANIMAL_TYPE, NatureAnimal))

#define NATURE_IS_ANIMAL(obj) \
   (G_TYPE_CHECK_INSTANCE_TYPE ((obj),  NATURE_ANIMAL_TYPE))

#define NATURE_ANIMAL_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_CAST ((klass), NATURE_ANIMAL_TYPE, NatureAnimalClass))

#define NATURE_IS_ANIMAL_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_TYPE ((klass),  NATURE_ANIMAL_TYPE))

#define NATURE_ANIMAL_GET_CLASS(obj) \
   (G_TYPE_INSTANCE_GET_CLASS ((obj),  NATURE_ANIMAL_TYPE, NatureAnimalClass))

typedef struct _NatureAnimal        NatureAnimal;
typedef struct _NatureAnimalClass   NatureAnimalClass;
//typedef struct _NatureAnimalPrivate NatureAnimalPrivate;

/**
 *  _NatureAnimal:
 *  @age: some gboolean
 *  @name: some gboolean
 *
 *   Private data
 */
struct _NatureAnimal
{
   GObject parent;

   int age;
   char *name;
   /*< private >*/
//   NatureAnimalPrivate *priv;
};



/**
 *  _NatureAnimalClass:
 *  @parent_class: some #gboolean
 *
 * This is the best widget, ever.
 */
struct _NatureAnimalClass
{
   GObjectClass parent_class;

   void (*eat)(NatureAnimal *self, char *msg);
   void (*cry)(NatureAnimal *self, char *msg);
   void (*myint)(NatureAnimal *self, my_int n);
   void (*usualint)(NatureAnimal *self, int n);
   void (*p_to_int)(NatureAnimal *self, int *pointer_to_int, int *arr);
   void (*get_data)(NatureAnimal *self);
};

GType nature_animal_get_type(void) G_GNUC_CONST;

NatureAnimal *nature_animal_new(const char *name, int age);//constructor


void nature_animal_eat(NatureAnimal *self, char *msg);
void nature_animal_cry(NatureAnimal *self, char *msg);
void nature_animal_myint(NatureAnimal *self, my_int n);


/**
 * nature_animal_uint:
 * @self: object instance:
 * @n: some parameter:
 *
 * Introspecting usual integer type
 */
void nature_animal_uint(NatureAnimal *self, int n);

/**
 * nature_animal_func:(skip)
 * @self:object instance:
 * @nn: some parameter in _func:
 */
void nature_animal_func(NatureAnimal *self, int nn);

/**
 * nature_animal_pint:
 * @self: object instance:
 * @n: (in): some parameter in pint:
 * @a:  (out) (array fixed-size=2): array:
 * function which returns pointer to int
 */
void nature_animal_pint(NatureAnimal *self, int *n, int **a);

void nature_animal_get_data(NatureAnimal *self);

//void nature_animal_do_action(NatureAnimal *self);

G_END_DECLS
#endif
