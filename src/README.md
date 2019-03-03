# README FIGHTER JET

## How to run the game

### COMPILE

    cmake CMakeLists.txt
    make

### RUN THE EXECUTABLE

    ./FighterJet

## CONTROLS
    The user can play by keyboard.
    Zooming and done using the mouse.

|Keyboard| Controls|
|-----|----|
|KEY 	|ACTION|
|Up arrow| 	Tilt up/Also used in helicam view for changing look angle|
|Down arrow |	Tilt down/Also used in helicam view for changing look angle|
|Left arrow |	Used in helcam view|
|Right arrow |	Used in helcam view|
|ESC |	Quit|
|w 	|move forward|
|a 	|Move left|
|s 	|Nothing|
|d 	|Move right|
|b | Bomb|
|q | Barrel Roll Counterclockwise|
|e | Barrel Roll Clockwise|
|v | Vertical loop|
| Space_bar| Shoot missile|

Mouse Controls
    Used in Helicam view for moving/rotating the camera.

## RULES 

### Basic
    Player has fuel(decreases with speed), health.
    Collect fuelups and healthups to survive.
    Dashboard has score, fuel, health, altitude, speed;
    Enemies are brilliant and start hitting more frequently after one succesful shot.
    Player DIes on reaching near a volcano.

### Camera_Views

|Key | View|
|--|--|
|0 | Towerview;Changes to the nearest tower automatically|
|1| Follow-up cam|
|2| FPS cam|
|3| Skyview cam|
|4| Missile View Cam|
|5| Bomb View Cam| 
|6| Helicam|
|V-Loop (automatic)| V-loop observer cam|

### Checkpoint

Checkpoints are shown to the user with the top green pointer.
Turn green on reaching
Enemies present at each check point and can have multiple cannons and lives to shoot you.
Number of enemies increases after each check point.
### Scoring 

|Object/Enemy| POINTS ADDED|
|--|--|
| Parachute | 100|
|Smoke Ring | ~100|
|Enemy using missiles | 200|
| Enemy using bombs | 250 |



  