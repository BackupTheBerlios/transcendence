Quest Altar 1.0
(c) 2003 Keelhaul
Keelhaul@t-online.de

Written using the 0.95 POL core.

Description
-----------
The quest altar scans its surface for 1-3 assigned items. If a correct item has been
placed, it is consumed by flames, otherwise nothing happens. Once all correct items
have been consumed, it either destroys an obstacle item (no multi) or unlocks a door/
container.

Installation
------------
Unzip the archive into your POL main directory, the files will be stored in
Drive:\YourPOLdir\pkg\items\altar\

Instructions
------------
- enter the desired mode (1 for obstacle destruction, 2 for unlocking)
- target up to 3 items, press ESC to skip unnecessary target prompts
- after the items have been targeted, the altar is active
- players must place all selected items onto its surface to complete the sequence
- once the sequence has been completed, the altar is no longer active

Notes
-----
- items are identified by their objtype, so it is recommended to use items with unique
  objtypes (e.g. custom items)
- you must select at least 1 item, or the setup procedure will abort
- items may not have the same objtype, or the setup procedure will abort
- tile surface is blue while active (scanning), otherwise grey
- if a Seer or above double clicks the tile while it is active, it will be reset and
  the staff member will be prompted to set it up
- if the default objtype of the altar tile is already taken on your shard, assign a new one
