# Lab 2: Синхронизация потоков с помощью мьютексов и неименованных семафоров (Đồng bộ hóa các luồng, sử dụng mutex và semaphore không định danh)
- Nội dung bài lab: Làm quen với việc sử dụng công cụ đông bộ hóa luồng: mutex và semaphore vô danh. 
 
## 1. Mutex
- Trên một hệ điều hành thường có nhiều chương trình (tác vụ -task) chạy đồng thời. Mutex giúp ngăn chặn việc 2 task cùng lúc truy cập vào cùng 1 tài nguyên (trong phạm vi bài lab và chiếu theo методичка thì ta gọi vùng tài nguyên đó là критический участок - critical area), register gọi chung là critical section của hệ thống trong cùng 1 thời điểm.
- Cơ chế của Mutex được dùng cho hardware và cả software (rất phổ biến).
- Hiểu đơn giản: Mutex có 1 chức năng gọi là lock(khóa). Nó sẽ khóa vùng CS (critical section) cho đến khi task 1 hoàn thành, thì nó mở khóa (unlock) cho task 2 thực thi nhiệm vụ của mình, tránh xung đột tài nguyên hệ thống.
 ví dụ mô tả bởi code:
 void task1()
 {
 //wait until unlock CS
 osMutexWait();
 //main activities
 @to do
 //unlock CS 
 osMutexRelease() // hàm giải phóng 
 }
 ## 2. Semaphore
 ![alt](http://media.thanhnt.com/2015/07/RTOS-Semaphore.png)
 Là kiểu dữ liệu biến hoặc trừu tượng được dùng để kiểm soát truy cập vào một tài nguyên chung bằng nhiều quy trình trong một hệ thống đồng thời, hoặc là 1 hệ điều hành đa nhiệm (theo wikipedia)
 - Để thỏa mãn yêu cầu loại trừ lẫn nhau của các luồng khi truy cập vào cùng tài nguyên hệ thống (CS) thì ta sử dụng semaphores.
 - Semaphores có thể chia thành: Nhị phân (Двоичные) và Tổng quát (Общие); hoặc là Định danh (Именованные) và Vô danh (Неименованные).
 - Semaphore nhị phân = Mutex - chứa chỉ 2 trạng thái: Capture (захвачен) và Release (Свободен).
  - Nếu CS bận, thì thread sẽ thực hiện capture (chụp) của Mutex, chặn và ko cho vào vùng CS. Việc chặn luồng này và việc xâm nhập vào CS được diễn ra chỉ khi mà tác vụ trước đó đã xâm nhập, đi ra khỏi CS và giải phóng cho mutex.
  - Semaphore khác Mutex ở điểm: 
   - Nhiều hơn giá trị trạng thái (status) được sử dụng trong bộ đếm. Nói cách khác, Semaphore hỗ trợ multi process. (Семафор отличается от мьютекса большим числом состояний за счет использования внутреннего счетчика. Это позволяет обеспечить большее разнообразие правил нахождения потоков в критическом участке.)  Ví dụ: Đối với Mutex, task nào lock tài nguyên (CS) thì chính task đó phải unlock CS. Còn đối với Semaphore thì cho phép task khác nào đó có thể unlock CS nếu cần thiết.
   - Khi một task đang giữ mutex, hệ điều hành cho phép xóa mutex đó nếu cần thiết. Còn Semaphore không hỗ trợ điều này.
   - Khi trạng thái ban đầu của bộ đếm Semaphore = 1, thì Semaphore tương đương Mutex. 
  - Mutex và Semaphore vô danh được dùng để đồng bộ hóa luồng trong cùng 1 vùng nhớ của bộ xử lý.
  - Semaphore định danh sử đụng dể đồng bộ hóa tiến trình (process) và sẽ được nghiên cứu ở các bài lab sau.
## 3. Các hàm trong bài lab
- Việc gọi hàm tạo Mutex, sẽ theo mấu sau:
 int pthread_mutex_init(pthread_mutex_t *mutex,
const pthread_mutexattr_t *attr),
где:
mutex – идентификатор мьютекса; //identificator Mutex
attr – указатель на структуру данных, описывающих атрибуты мьютекса //con trỏ đến cấu trúc dữ liệu, mô tả thuộc tính của Mutex.
- Để vào vùng critical section (CS) của Mutex cần gọi hàm:
int pthread_mutex_lock(pthread_mutex_t *mutex).
- Để thoát khỏi CS cần gọi hàm:
int pthread_mutex_unlock(pthread_mutex_t *mutex).
- Hàm để phá hủy Mutex:
int pthread_mutex_destroy(pthread_mutex_t *mutex).
- Hàm tạo semaphore vô danh:
int sem_init(sem_t *sem, int shared, unsigned int value),
где:
sem – идентификатор семафора; //identificator Semaphore
shared – индикатор использования семафора потоками или процессами;// chỉ số sử dụng luồng hoặc tiến trình
value – начальное значение счетчика семафора. // giá trị ban đầu của bộ đếm semaphore.
- Hàm vào vùng CS của Semaphore vô danh:
int sem_wait(sem_t *sem).
- Hàm thoát khỏi vùng CS của Semaphore vô danh:
int sem_post(sem_t *sem).
- Phá hủy semaphore gọi hàm:
int sem_destroy(sem_t *sem).



 
