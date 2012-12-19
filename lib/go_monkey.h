
#ifndef _GO_MONKEY_H
#define _GO_MONKEY_H

#include <glib-object.h>
#include "go_nature.h"

G_BEGIN_DECLS

#define NATURE_MONKEY_TYPE nature_monkey_get_type()

#define NATURE_MONKEY(obj)   \
(G_TYPE_CHECK_INSTANCE_CAST ((obj), NATURE_MONKEY_TYPE, NatureMonkey))

#define NATURE_IS_MONKEY(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),  NATURE_MONKEY_TYPE))

#define NATURE_MONKEY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), NATURE_MONKEY_TYPE, NatureMonkeyClass))

#define NATURE_IS_MONKEY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass),  NATURE_MONKEY_TYPE))

#define NATURE_MONKEY_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj),  NATURE_MONKEY_TYPE, NatureMonkeyClass))

typedef struct _NatureMonkey        NatureMonkey;
typedef struct _NatureMonkeyClass   NatureMonkeyClass;
typedef struct _NatureMonkeyPrivate NatureMonkeyPrivate;

struct _NatureMonkey
{
  NatureAnimal parent;
  NatureMonkeyPrivate *private_data;

  int monkey_public;
};

struct _NatureMonkeyClass
{
   NatureAnimalClass parent_class;
};

GType nature_monkey_get_type(void) G_GNUC_CONST;

NatureAnimal *nature_monkey_new(const char *name, int age);
void nature_monkey_set_private(NatureAnimal *_self, char *_kind, char *_place);
void nature_monkey_print_private(NatureAnimal *_self);

G_END_DECLS
#endif
