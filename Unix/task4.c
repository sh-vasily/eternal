#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
 
// посчитать размер afqkf
long long calc_size_file( char* dir );
// вывевсти на экран тип, размер, имя файлов из указанной директории
void print_dir( char* dir );
// определить тип файла
char display_file_type ( int st_mode );
 
 
int main( int argc, char* argv[] ) {
 
    if ( argc < 2 ) { // если неверно задан аргумент
        // выводим сообщение об ошибке
        fprintf( stderr, "Invalid argument! Use: viewdir <directory>\n" );
        return EXIT_FAILURE; // выходим из программы
    }
    // выводим сообщение о том какую директорию сканируем
    for(int i = 1; i <argc; ++i)
    {
        printf( "Directory scan of  %s: \n", argv[ i ] );
        print_dir( argv[ i ] ); // выводим на экран тип, размер, имя файлов указанной директории
    }
    return EXIT_SUCCESS;
}
 
void print_dir( char* dir ){
    DIR *dp; // поток каталога
    struct dirent *entry; // для имени и индекса файла
    struct stat statbuf; // для информации о файле
 
    if ( ( dp = opendir( dir ) ) == NULL ) { // если не смогли открыть поток каталога
        fprintf( stderr, "cannot open directory: %s\n", dir ); // выводим сообщение об ошибке
        return; // выходим из функции
    }
 
    chdir( dir ); // перемещаемся в указанную директорию
 
    while ( ( entry = readdir( dp ) ) != NULL ) { // цикл по всем файлам указанной директории
        lstat( entry->d_name, &statbuf ); // считываем информацию о файле в структуру
 
        if ( S_ISDIR( statbuf.st_mode ) ) { // если это директория
 
            // проверяем является ли она . или ..
            if ( strcmp( ".", entry->d_name ) == 0 ||
                    strcmp( "..", entry->d_name ) == 0 ) // и если да,
                continue; // то игнорируем ее, возвращаясь в начало цикла
 
            // считаем размер директории
            long long size = calc_size_file( entry->d_name );
 
            // если размер посчитать не удалось, то
            if ( size == -1 )
                printf ( "%c\t%s\t\t%s\n", 'd', "unknow", entry->d_name ); // выводим на экран информацию об этом
            else // а если все в порядке
                // выводим информацию о директории
                printf( "%c\t%lld\t\t/%s\n", 'd', ( long long )statbuf.st_size + size, entry->d_name );
        }
        else{ // иначе - если это НЕ директория, то выводим информацию о файле
            printf( "%c\t%lld\t\t/%s\n", display_file_type( statbuf.st_mode ), ( long long )statbuf.st_size, entry->d_name );
        }
    }
 
    closedir( dp ); // закрываем указаннню директорию
}
 
long long calc_size_file( char* dir ) {
 
    static int err_code = 0; // для запоминания ошибки
    long long  sum_size = 0; // для размера файла
 
    DIR *dp; // поток каталога
    struct dirent *entry; // для имени и индекса файла
    struct stat statbuf; // для информации о файле
 
    if ( ( dp = opendir( dir ) ) == NULL ) {  // если не смогли открыть поток каталога
        err_code = 1; // запоминаем это
        return -1;
    }
 
    // а если все нормально, то
    chdir( dir );  // перемещаемся в указанную директорию
    // цикл по всем файлам указанной директории
    while ( ( entry = readdir( dp ) ) != NULL && !err_code) {
        lstat( entry->d_name, &statbuf ); // считываем информацию о файле в структуру
 
        if ( S_ISDIR( statbuf.st_mode ) ) { // если это директория
 
            // проверяем является ли она . или ..
            if ( strcmp( ".", entry->d_name ) == 0 ||
                    strcmp( "..", entry->d_name ) == 0 ) // и если да,
                continue; // то игнорируем ее, возвращаясь в начало цикла
 
            // прибавляем к общему размеру размер текущей директории
            // ( 4096 -  обычно такой размер имеют директории, но если в директории МНОГО данных, то размер может быть и больше )
            // далее считаем размер всех файлов, содержащихся в текущей директории и прибавляем к общему размеру
            // а чтобы посчитать - РЕКУРСИВНО вызововем нашу функцию и т.о. спустимся на уровень ниже
            sum_size += ( long long )statbuf.st_size + calc_size_file( entry->d_name ); // РЕКУРСИЯ
 
            if ( err_code ) // если была ошибка,
                return -1; // то завершаем функцию с ошибочным кодом возврат
 
        }
        else{
            // иначе - если это НЕ директория, то прибавляем к общему размеру текущей директории размер данного файла
            sum_size += ( long long )statbuf.st_size;
        }
    }
 
 
    // после того как закончили считать размер очередной директории - перемещаемся на уровень выше
    // т.е. в предыдущию директорию
    chdir( ".." );
    closedir( dp ); // закрываем поток каталога
 
    return sum_size; // а если все нормально, то возвращаем искомый размер
}
 
char display_file_type ( int st_mode ) {
    // тут все ясно
    switch ( st_mode & S_IFMT ) {
        case S_IFDIR:
            return 'd';
        case S_IFCHR:
            return 'c';
        case S_IFBLK:
            return 'b';
        case S_IFREG:
            return 'r';
        case S_IFLNK:
            return 'l';
        case S_IFSOCK:
            return 's';
        case S_IFIFO:
            return 'f';
        default:
            return 'u';
    }
}
