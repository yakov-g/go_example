import sys
import pygtk
pygtk.require('2.0')

from gi.repository import Nature
from gi.repository import Mankind
from gi.repository import Digital


class AA(Digital.Comp, Nature.Animal):
    def ff(self):
        print "ff func"


#dc = AA()
#dc.eat("foooooooooooooooooood")
#dc.compute("compuuuuuuuuuuuuuuuuuuute")
#dc.reboot("reboot")
#exit()

"""
dc = Digital.Comp.new("asdf", 3)
dc.compute("compute")
dc.reboot("reboot")
exit()
"""

a = Nature.Animal.new("Animal", 2)

a.eat("food")
a.cry("wow")
a.uint(698521147)
ee = 9
r= a.pint(ee)
print r

exit()

#a.myint(123)
print "printing with print : ", a.age, a.name



print ""
m = Nature.Monkey.new("Monkey", 5)
m.cry("Moygli")
m.eat("banana")
m.get_data()

#del m

print ""
h = Mankind.Human.new("Jack", 26)
h.cry("Hoooray")
h.eat("Hamburger")
h.get_data()


"""
Clutter.init(sys.argv)

stage = Clutter.Stage()

stage_color = Clutter.Color();
actor_color = Clutter.Color();
tri_color = Clutter.Color();

stage_color.from_pixel(0x000000ff);
actor_color.from_pixel(0x00fff0ff);
tri_color.from_pixel(0xff00ff80);

#stage_color = Clutter.Color(0, 0, 0, 255)
#actor_color = Clutter.Color(255, 255, 255, 99)

stage.set_size(200, 200)
stage.set_color(stage_color)



rect = Clutter.Rectangle.new_with_color(actor_color)
rect.set_size(100, 100)
rect.set_position(20, 20)

rect.set_rotation(Clutter.RotateAxis.X_AXIS, -45, 0, 0, 0)

stage.add_actor(rect)
rect.show()

tri = Tut.Triangle.new_with_color(tri_color)
tri.set_size(150, 100)
tri.set_position(20, 20)
stage.add_actor(tri)
tri.show()
"""

