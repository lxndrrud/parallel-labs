#include <mpi/mpi.h>
#include <iostream>
int main (int argc, char *argv[])
{
// Объявляем переменные int i, rank, size, namelen;
char name[MPI_MAX_PROCESSOR_NAME]; MPI::Status stat;
//Инициализируем подсистему MPI MPI::Init (argc, @argv);
//Получаем информацию о процессе size = MPI::COMM_WORLD.Get_size (); rank = MPI::COMM_WORLD.Get_rank ();
MPI::Get_processor_name (name, namelen);
if (rank == 0) {
// Находимся в головном процессе
std::cout << "Hello world: rank " << rank << " of " << size << " running on " << name << "\n";
// Собираем информацию от всех прочих процессов for (i = 1; i < size; i++) {
MPI::COMM_WORLD.Recv (&rank, 1, MPI_INT, i, 1, stat); MPI::COMM_WORLD.Recv (&size, 1, MPI_INT, i, 1, stat); MPI::COMM_WORLD.Recv (&namelen, 1, MPI_INT, i, 1,
stat);
MPI::COMM_WORLD.Recv (name, namelen + 1, MPI_CHAR, i, 1, stat);
std::cout << "Hello world: rank " << rank << " of " << size << " running on " << name << "\n";
}
}else {
//Находимся в дочернем процессе
//Необходимо отправить информацию о себе головному процессу
MPI::COMM_WORLD.Send (&rank, 1, MPI_INT, 0, 1); MPI::COMM_WORLD.Send (&size, 1, MPI_INT, 0, 1); MPI::COMM_WORLD.Send (&namelen, 1, MPI_INT, 0, 1); MPI::COMM_WORLD.Send (name, namelen + 1, MPI_CHAR, 0, 1);
}
// Освобождаем подсистему MPI MPI::Finalize ();
return (0);
}