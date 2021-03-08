#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <ctime>

#include "c960generator.h"

using namespace std;

int main()
{
    C960Generator c960; // Por defecto es "RNBQK" pero puede ponerse c960("TCADR") por ejemplo si se quiere usar notacion en Español
    unsigned int random_id;

    // EJEMPLO DE USO. Mostrar TODAS las combinaciones.
    // SAMPLE OF USE. Show ALL positions.

    for (int n = 0; n <960; n++)
        cout << setw(3) << n << " - " << c960.getPosition(n) << "  ";

    // EJEMPLO DE USO. Mostrar combinación aleatoria.
    // SAMPLE OF USE. Show random position.

    srand(time(NULL));
    random_id = rand() % 959;
    c960.setStringOfPieces("TCADR");  // Spanish Notation
    cout << endl << "And a random position with Spanish Notation..." <<
            endl << "Y una posición aleatoria con Notación Española... " <<
            endl << random_id << " - " << c960.getPosition(random_id) << endl;

    return 0;
}
