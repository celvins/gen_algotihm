#include "gen.h"
#include "algoritm.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    gen w;
    w.show();
    return app.exec();
}
