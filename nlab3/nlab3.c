//Подключаем необходимые заголовки
#include <mpi/mpi.h> 
#include <stdio.h> 
#include <math.h>
//Функция для промежуточных вычислений double f(double a)
double f(double a)
{
    return (4.0 / (1.0 + a*a));
}
//Главная функция программы
int main(int argc,char *argv[])
{
    // Объявляем переменные
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643; double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime; int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    // Инициализируем подсистему MPI
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    /* // Выводим номер потока в общем пуле
    fprintf(stdout,"Process %d of %d is on %s\n", myid, numprocs, processor_name); fflush(stdout);
    */
    while (!done) {
        // Если это головной процесс, спрашиваем пользователя о
        // количестве интервалов if (myid == 0) {
        fprintf(stdout, "Enter the number of intervals: (Non-digit quits) ");
        fflush(stdout);
        if (scanf("%d",&n) != 1) {
            fprintf( stdout, "No number entered; quitting\n" ); 
            //n = 0;
            break;
        }
        startwtime = MPI_Wtime();
    }
    // Рассылаем количество интервалов всем процессам //(в том числе и себе самому)
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); if (n == 0)
        done = 1; else {
        h = 1.0 / (double) n; sum = 0.0;
        // Обсчитывает точки, "закрепленные" за процессом for (i = myid + 1; i <= n; i += numprocs) {
        x = h * ((double)i - 0.5); sum += f(x);
    }
    mypi = h * sum;
    // Собираем результаты со всех процессов и складываем все
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // Если это головной процесс, выводим полученные результаты
    if (myid == 0) {
        printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
        endwtime = MPI_Wtime();
        printf("wall clock time = %f\n", endwtime - startwtime);
        fflush( stdout );
    }
    return 0;
}
