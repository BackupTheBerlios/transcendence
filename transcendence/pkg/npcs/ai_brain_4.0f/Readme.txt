This is a new concept for doing AI in POL.
It has been used for about a year on a shard
designed by Myrathi and Austin known under the
following names:

Thomas' Scottish Sheep Exchange
The Sanctuary: Shadow's Edge
TSSE

They started the shard from pol.exe and nothing
more. As a result, they recognized that if they
wanted to make a new AI for POL, they would need to
make it not only compatable with any distro shard
but also any shard that was built from the ground up.

The brain's primary purpose is to remove a build up
of linear includes and AI scripts; and to have a one
script fits all deal. As a result, the brain has a strong
ability to make an npc do multiple things at the same
time and many nerves will snap in to different npcs in
different arrangements to save work and time.

It has almost taken 9 months of work, not straight work,
but definately work to get this A.I. where it is now.
They want to share it with other people in the POL
"community" in hopes that other people will contribute
to it, and not just run off with it and do their own
thing as is unfortunately typically done.

We would like to extend a warm thanks to the following
people for offering insights, testing and other help
with the development of this A.I.:
Adam, aka Madman ATW
Birdy
Chris, aka Bishop Ebonhand
Michael Branin

-Myrathi & Austin




The npcdesc.cfg for this AI system has some extra
parameters. Documentation will show up sooner or
later explaining what the different settings are
that the brain uses directly. For nerves, you can
make up any of your own settings and these are passed
to them by the brain.

Included are some sample nerves that should help
people get them going.

It is not reccomended that this AI system be installed
on a fully functioning shard because the npcdesc.cfg
only has a few entries to outline ways to do things and
only essential nerves. This is a package AI system and
hopefully soon the pol/scripts/ai method will be phased
out. The AI still relies on the pol/config/npcdesc.cfg
though simply because it is a bit of a pain to use packaged
npcs.

By default, the include paths are setup for the AI to be put
right in /pol/pkg/ai_brain. Place it there, and setup your
npcdesc.cfg to be compatable with this AI system. There are
two ways to do this:
1. Just use the one provided.
2. Copy the ones in the one provided to the existing one
and make sure you dont have duplicate template names

This AI system will take some getting used to for those who
give it a shot. But in the long run, we hope it makes the
task of making unique AI scripts for npcs significantly easier
and overall, less load stressing.

In time, people may use the cprop settings to create a
tamed listening script right in the brain, or npcs that
can talk to each other with event forwarding. The  possibilties
are only limited by people's cooperation and imagination.

-Austin
