```html
<h1>Termdax</h1>
```
```txt
A c++ library to create shapes in the console
```
<hr />

```cpp
#include <iostream>
#include "src/termdax.cpp"

int main()
{
    Termdax termdax;
    termdax.createRectangle(0,0,5,5,'#');
    termdax.Draw();
    std::cin.get();   
    return 0;
}
```
