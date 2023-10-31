#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int my_message = 0;
   int sender_id = 1; // encargado de enviar el multicast
   int receiver_id = 1; // encargado de recolectar todos los resultados
   const int NUM_VECTORS = 3; // debe ser igual al num de procesos
   const int VECTOR_SIZE = 5; 
   float data[NUM_VECTORS][VECTOR_SIZE] = {{11, 12, 13, 14, 15},
                                           {16, 17, 18, 19, 20},
                                           {21, 22, 23, 24, 25}};
   float message[VECTOR_SIZE];  

   float data_to_be_collected[NUM_VECTORS];

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);
   cout << "Hi from process " << process_id << " on " << host_name << "\n";
   if (process_id == MASTER) 
      cout << "MASTER: The number of MPI processes is " << num_processes << "\n";
/*   
   if (process_id == sender_id) {
      my_message = 111;
   }
   cout << process_id << " Variable my_message = " << my_message << endl;
   MPI_Bcast(&my_message, 1, MPI_INT, sender_id, MPI_COMM_WORLD);
   cout << process_id << " Recibí my_message = " << my_message << endl;
*/
   // matener consistencia entre vectores a repartir y numero de procs existentes
   if (num_processes == NUM_VECTORS)  {
      MPI_Scatter(&data, 
                  VECTOR_SIZE, 
                  MPI_FLOAT, 
                  &message, 
                  VECTOR_SIZE, 
                  MPI_FLOAT, 
                  sender_id, 
                  MPI_COMM_WORLD);
      cout << "Scatter Proceso " << process_id 
            << " " << message[0] 
            << " " << message[1] 
            << " " << message[2] 
            << " " << message[3]
            << " " << message[4] << endl; 

      // codigo ejecutado por cada hilo
      float total = 0;
      for (int i = 0; i < VECTOR_SIZE; i++) {
         total += message[i];
      }

      float promedio = total / VECTOR_SIZE;
      MPI_Gather(&promedio, 1, 
                 MPI_FLOAT, 
                 data_to_be_collected, 
                 1, 
                 MPI_FLOAT, 
                 receiver_id, 
                 MPI_COMM_WORLD);

      cout << "Gather Proceso " << process_id  
            << " " << data_to_be_collected[0] 
            << " " << data_to_be_collected[1]
            << " " << data_to_be_collected[2] << endl; 

      float reduction_result = 0.0;

      MPI_Reduce(&promedio, 
                 &reduction_result, 
                 1, 
                 MPI_FLOAT, 
                 MPI_MIN, 
                 receiver_id, 
                 MPI_COMM_WORLD);

      cout << "Reduce Proceso " << process_id << " " << reduction_result << endl; 


   } else {
      cout << "Error fatal";
   }
 



   MPI_Finalize();

   return 0;
}