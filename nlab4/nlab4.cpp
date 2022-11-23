#include <mpi/mpi.h>
#include <iostream>

int main (int argc, char *argv[])
{
    // Объявляем переменные 
    int i, rank, size, namelen;
    char name[MPI_MAX_PROCESSOR_NAME]; MPI::Status stat;
    //Инициализируем подсистему 
    MPI::Init(argc, argv);
    //Получаем информацию о процессе 
    size = MPI::COMM_WORLD.Get_size (); 
    rank = MPI::COMM_WORLD.Get_rank ();
    MPI::Get_processor_name (name, namelen);
    if (rank == 0 ) {
        int rankBefore = rank;
        // Находимся в одном из головных процессе
        // Собираем информацию от всех прочих процессов 
        MPI::COMM_WORLD.Recv (&rank, 1, MPI_INT, 2, 1, stat); 
        MPI::COMM_WORLD.Recv (&size, 1, MPI_INT, 2, 1, stat); 
        MPI::COMM_WORLD.Recv (&namelen, 1, MPI_INT, 2, 1, stat);
        MPI::COMM_WORLD.Recv (name, namelen + 1, MPI_CHAR, 2, 1, stat);
        std::cout << "Привет процессу " << rankBefore << " от " << rank << ", запущенному на " << name << "\n";
    } else if (rank == 1) {
        int rankBefore = rank;
        // Находимся в головном процессе
        // Собираем информацию от всех прочих процессов 
        MPI::COMM_WORLD.Recv (&rank, 1, MPI_INT, 3, 1, stat); 
        MPI::COMM_WORLD.Recv (&size, 1, MPI_INT, 3, 1, stat); 
        MPI::COMM_WORLD.Recv (&namelen, 1, MPI_INT, 3, 1, stat);
        MPI::COMM_WORLD.Recv (name, namelen + 1, MPI_CHAR, 3, 1, stat);
        std::cout << "Привет процессу " << rankBefore << " от " << rank << ", запущенному на " << name << "\n";
    } else if (rank == 2) {
        //Находимся в дочернем процессе
        //Необходимо отправить информацию о себе головному процессу
        MPI::COMM_WORLD.Send (&rank, 1, MPI_INT, 0, 1); 
        MPI::COMM_WORLD.Send (&size, 1, MPI_INT, 0, 1); 
        MPI::COMM_WORLD.Send (&namelen, 1, MPI_INT, 0, 1); 
        MPI::COMM_WORLD.Send (name, namelen + 1, MPI_CHAR, 0, 1);
    } else if (rank == 3) {
        //Находимся в дочернем процессе
        //Необходимо отправить информацию о себе головному процессу
        MPI::COMM_WORLD.Send (&rank, 1, MPI_INT, 1, 1); 
        MPI::COMM_WORLD.Send (&size, 1, MPI_INT, 1, 1); 
        MPI::COMM_WORLD.Send (&namelen, 1, MPI_INT, 1, 1); 
        MPI::COMM_WORLD.Send (name, namelen + 1, MPI_CHAR, 1, 1);
    }
    // Освобождаем подсистему 
    MPI::Finalize ();
    return 0;
}