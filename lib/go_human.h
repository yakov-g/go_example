
#ifndef _GO_HUMAN_H
#define _GO_HUMAN_H

#include <glib-object.h>
#include "go_nature.h"

G_BEGIN_DECLS

#define MANKIND_HUMAN_TYPE mankind_human_get_type()

#define MANKIND_HUMAN(obj)   \
(G_TYPE_CHECK_INSTANCE_CAST ((obj), MANKIND_HUMAN_TYPE, MankindHuman))

#define MANKIND_IS_HUMAN(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),  MANKIND_HUMAN_TYPE))

#define MANKIND_HUMAN_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), MANKIND_HUMAN_TYPE, MankindHumanClass))

#define MANKIND_IS_HUMAN_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass),  MANKIND_HUMAN_TYPE))

#define MANKIND_HUMAN_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MANKIND_HUMAN_TYPE, MankindHumanClass))

typedef struct _MankindHuman        MankindHuman;
typedef struct _MankindHumanClass   MankindHumanClass;
typedef struct _MankindHumanPrivate MankindHumanPrivate;

struct _MankindHuman
{
  NatureAnimal parent;
  MankindHumanPrivate *private_data;

};

struct _MankindHumanClass
{
   NatureAnimalClass parent_class;
};

GType mankind_human_get_type(void) G_GNUC_CONST;

NatureAnimal *mankind_human_new(const char *name, int age);//constructor
void mankind_human_print_private(NatureAnimal *_self);

G_END_DECLS
#endif
