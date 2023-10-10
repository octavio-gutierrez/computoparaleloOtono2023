#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   // Le ponemos parter 0 a raíz de que asumimos que sender.exe se ejecuta 
   // en segundo lugar
   int partner = 0;
   int num_elementos_enviar = 5;
   int mensaje[num_elementos_enviar] = {11, 12, 13, 14, 15};
   int etiqueta = 101; 
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);
   cout << "Hi from process " << process_id << " on " << host_name << "\n";

   MPI_Send(&mensaje, 
            num_elementos_enviar, 
            MPI_INT, 
            partner, 
            etiqueta, 
            MPI_COMM_WORLD);
    cout << "I just send the array" << endl;
   MPI_Finalize();

   return 0;
}