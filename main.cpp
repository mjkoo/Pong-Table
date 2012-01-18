#include <iostream>

#include <sqlite.h>

#include <Display.h>

using namespace std;

int
main(int argc, char **argv)
{
    Display disp("/dev/ttyO1");

    disp.clear();
    disp.print("Lorem ipsum dolor sit amet, porttitor placerat proin augue nec, mi sapien magna sodales lacinia inceptos, lacinia odio sit sit vel porta. In adipiscing. Morbi mattis vivamus aptent dui, vivamus cum eget at quis, vestibulum pharetra integer eget, metus nonummy ridiculus lacus libero porttitor, mi vitae arcu feugiat euismod imperdiet nec. Neque venenatis vehicula at in felis rhoncus, erat elit sodales ut maecenas veniam. Diam praesent, fusce scelerisque ac quisque volutpat lacinia bibendum. Amet dignissim donec quis velit donec, quam odio, at inceptos sed massa libero, quisque ut orci, erat euismod. Porta semper praesent quis turpis ac scelerisque, lectus sed libero. Dictum gravida ridiculus, in turpis id mauris cras commodo, vel facilisis, ipsum eu. Molestie mi urna pulvinar accumsan sodales mauris, dictum ut blandit eu nec vivamus.");

    return 0;
}
