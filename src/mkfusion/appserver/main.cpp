#include "qmkfusionservice.h"


int main(int argc, char **argv)
{
    QMKFusionService service(argc, argv);
    return service.exec();
}
