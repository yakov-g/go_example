
#ifndef _GO_DIGITAL_H
#define _GO_DIGITAL_H

#include <glib-object.h>

G_BEGIN_DECLS

#define DIGITAL_COMP_TYPEEE digital_comp_get_type()

#define DIGITAL_COMP(obj)   \
   (G_TYPE_CHECK_INSTANCE_CAST ((obj), DIGITAL_COMP_TYPEEE, DigitalComp))

#define DIGITAL_IS_COMP(obj) \
   (G_TYPE_CHECK_INSTANCE_TYPE ((obj),  DIGITAL_COMP_TYPEEE))

#define DIGITAL_COMP_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_CAST ((klass), DIGITAL_COMP_TYPEEE, DigitalCompClass))

#define DIGITAL_IS_COMP_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_TYPE ((klass),  DIGITAL_COMP_TYPEEE))

#define DIGITAL_COMP_GET_CLASS(obj) \
   (G_TYPE_INSTANCE_GET_CLASS ((obj),  DIGITAL_COMP_TYPEEE, DigitalCompClass))

typedef struct _DigitalComp        DigitalComp;
typedef struct _DigitalCompClass   DigitalCompClass;
//typedef struct _DigitalCompPrivate DigitalCompPrivate;

struct _DigitalComp
{
   GObject parent;

   int age;
   char *name;
   /*< private >*/
//   DigitalCompPrivate *priv;
};

struct _DigitalCompClass
{
   GObjectClass parent_class;

   void (*compute)(DigitalComp *self, char *msg);
   void (*reboot)(DigitalComp *self, char *msg);
   void (*halt)(DigitalComp *self);
};

GType digital_comp_get_type(void) G_GNUC_CONST;

DigitalComp *digital_comp_new(const char *name, int age);//constructor


void digital_comp_compute(DigitalComp *self, char *msg);
void digital_comp_reboot(DigitalComp *self, char *msg);
void digital_comp_halt(DigitalComp *self);

//void digital_comp_do_action(DigitalComp *self);

G_END_DECLS
#endif
