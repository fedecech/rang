# rang

Compiler and VM for rang language.

```rang
module Actor exposing *;

type Actor{
    string name;
    string sname;
    list<string> skills;
}

Actor __Actor__(string name, ...) => (Actor){.name = name, ...};

string [Actor as a]name() => a.name

//other file
import Actor;
from Actor import __Actor__, name;

Actor actor = __Actor__(name, ...);
actor.name();
[actor]name();
```
