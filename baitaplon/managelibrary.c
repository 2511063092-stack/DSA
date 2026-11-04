#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. KHAI BÁO CẤU TRÚC DỮ LIỆU 

// 1.1. Cấu trúc Sách
typedef struct Book_info {
    char id_book[20];       // Mã sách
    char name_book[100];    // Tên sách
    char author[50];        // Tác giả
    char publisher[50];     // Nhà xuất bản
    int year_publish;       // Năm xuất bản
    int quantity;           // Số lượng còn trong kho (>0: Còn, 0: Hết)
    int borrow_count;       // Tổng số lượt sách được mượn
} Book_info;

typedef struct Book {
    Book_info data;         // Thông tin của cuốn sách
    struct Book *next;      // Con trỏ trỏ tới cuốn sách tiếp theo trong danh sách
} Book;

// 1.2. Cấu trúc Độc giả
typedef struct Reader_info {
    char id_reader[20];     // Mã độc giả
    char name_reader[50];   // Họ tên độc giả
    char class_name[20];    // Lớp
    char phone[15];         // Số điện thoại
    int current_borrowed;   // Số sách đang mượn hiện tại
} Reader_info;

typedef struct Reader {
    Reader_info data;       // Thông tin của độc giả
    struct Reader *next;    // Con trỏ trỏ tới độc giả tiếp theo trong danh sách
} Reader;

// 1.3. Cấu trúc Phiếu Mượn/Trả (Lịch sử mượn)
typedef struct BorrowData {
    char id_reader[20];     // Mã độc giả mượn
    char id_book[20];       // Mã sách mượn
    char borrow_date[15];   // Ngày mượn
    char return_date[15];   // Ngày trả
    int status;             // Trạng thái: 1 = Đang mượn, 0 = Đã trả
} BorrowData;

typedef struct Borrow {
    BorrowData data;        // Thông tin phiếu mượn
    struct Borrow *next;    // Con trỏ trỏ tới phiếu mượn tiếp theo trong danh sách
} Borrow;

// 2. CÁC HÀM THỰC HIỆN CHỨC NĂNG CHƯƠNG TRÌNH 

// 2.1. Các hàm khởi tạo Node mới 

// 2.1.1. Hàm tạo một Node sách mới 
Book *makeBook(Book_info x){
    Book *newbook = (Book*)malloc(sizeof(Book)); // cấp phát vùng nhớ động cho 1 node sách
    if(newbook != NULL){
        x.borrow_count = 0; // sách mới thêm vào có lượt mượn ban đầu = 0
        newbook->data = x; // gán thông tin sách x vào node
        newbook->next = NULL; // node mới tạo chưa nối đi đâu nên next = NULL
    }
    return newbook; // trả về địa chỉ node sách mới tạo
}

// 2.1.2. Hàm tạo một Node độc giả mới 
Reader *makeReader(Reader_info x){
    Reader *newreader = (Reader*)malloc(sizeof(Reader)); // cấp phát vùng nhớ cho 1 node độc giả
    if(newreader != NULL){
        x.current_borrowed = 0; // độc giả mới tạo chưa mượn cuốn nào (= 0)
        newreader->data = x; // gán thông tin độc giả x vào node
        newreader->next = NULL;
    }
    return newreader;
}

// 2.1.3. Hàm tạo một Node phiếu mượn mới 
Borrow *makeBorrow(BorrowData x){
    Borrow *newborrow = (Borrow*)malloc(sizeof(Borrow)); // cấp phát vùng nhớ cho 1 phiếu mượn
    if(newborrow != NULL){
        x.status = 1; // mặc định khi mới tạo phiếu là trạng thái đang mượn (1)
        strcpy(x.return_date, "Dang muon"); // copy chuỗi "Dang muon" vào ngày trả
        newborrow->data = x;
        newborrow->next = NULL;
    }
    return newborrow;
}

// 2.2. Các hàm quản lý sách 

// 2.2.1. Hàm tìm sách theo mã sách 
Book *findBook(Book *head, char id_book[]){
    while(head != NULL){
        // so sánh 2 chuỗi: nếu bằng 0 nghĩa là 2 mã sách giống hệt nhau
        if(strcmp(head->data.id_book, id_book) == 0) return head; // tìm thấy thì trả về địa chỉ node sách đó
        head = head->next; // nhảy sang kiểm tra cuốn sách tiếp theo
    }
    return NULL; // duyệt hết danh sách mà không tìm thấy thì trả về NULL
}

// 2.2.2. Hàm thêm sách mới vào cuối danh sách
int addBook(Book **head, Book_info new_data){
    // prev (previous): con trỏ giữ node đứng trước | curr (current): con trỏ duyệt node hiện tại
    Book *prev = NULL, *curr = *head;
    while(curr != NULL){
        if(strcmp(curr->data.id_book, new_data.id_book) == 0) return 0; // trả về 0 nếu bị trùng mã sách
        prev = curr; // lưu lại node hiện tại trước khi nhảy sang node kế tiếp
        curr = curr->next;
    }
    Book *newbook = makeBook(new_data); // tạo node sách mới từ dữ liệu nhập vào
    if(newbook == NULL) return -1; // trả về -1 nếu lỗi đầy bộ nhớ RAM
    if(prev == NULL) *head = newbook; // nếu danh sách đang rỗng (prev == NULL) thì gán làm node đầu tiên
    else prev->next = newbook; // nếu đã có sách thì nối node mới vào sau node cuối cùng (prev)
    return 1; // trả về 1 báo hiệu thêm sách thành công
}

// 2.2.3. Hàm xóa sách theo mã sách
int deleteBook(Book **head, char id_book[]){
    if(*head == NULL) return 0; // danh sách đang rỗng thì trả về 0
    Book *curr = *head; // curr (current): con trỏ chạy để tìm node cần xóa
    Book *prev = NULL;  // prev (previous): con trỏ giữ node đứng ngay trước curr
    
    // lặp khi chưa hết danh sách và mã sách của curr vẫn khác mã sách cần xóa
    while(curr != NULL && strcmp(curr->data.id_book, id_book) != 0){
        prev = curr; // lưu vết lại node đứng trước
        curr = curr->next; // cho curr nhảy sang node tiếp theo
    }
    if(curr == NULL) return 0; // duyệt hết danh sách mà không tìm thấy sách cần xóa
    if(prev == NULL) *head = curr->next; // nếu xóa ngay node đầu tiên thì cập nhật lại *head sang node thứ 2
    else prev->next = curr->next; // nếu xóa ở giữa/cuối thì nối node trước (prev) vòng qua node sau của curr
    free(curr); // giải phóng vùng nhớ của node sách bị xóa
    return 1; // trả về 1 báo hiệu xóa thành công
}

// 2.2.4. Hàm sửa thông tin sách
int updateBook(Book *head, char id_book[], Book_info updated_data){
    Book *target = findBook(head, id_book); // target: con trỏ trỏ tới node sách cần sửa vừa tìm được
    if(target == NULL) return 0; // không tìm thấy sách để sửa

    strcpy(updated_data.id_book, target->data.id_book); // copy giữ nguyên mã sách cũ không cho đổi
    updated_data.borrow_count = target->data.borrow_count; // giữ nguyên tổng số lượt đã mượn cũ
    target->data = updated_data; // ghi đè thông tin mới vào node target
    return 1; // sửa thành công
}

// 2.2.5. Hàm kiểm tra số lượng sách còn trong kho
int checkBookStock(Book *head, char id_book[]){
    Book *target = findBook(head, id_book); // tìm cuốn sách theo mã
    if(target == NULL) return -1; // trả về -1 nếu mã sách không tồn tại
    else return target->data.quantity; // trả về số lượng sách hiện còn trong kho
}

// 2.3. Các hàm quản lý độc giả

// 2.3.1. Hàm tìm độc giả theo mã độc giả
Reader *findReader(Reader *head, char id_reader[]){
    while(head != NULL){
        if(strcmp(head->data.id_reader, id_reader) == 0) return head; // tìm thấy thì trả về địa chỉ node độc giả
        head = head->next;
    }
    return NULL; // không tìm thấy
}

// 2.3.2. Hàm thêm độc giả mới vào cuối danh sách
int addReader(Reader **head, Reader_info new_data){
    Reader *prev = NULL, *curr = *head; // prev: node đứng trước | curr: node hiện tại
    while(curr != NULL){
        if(strcmp(curr->data.id_reader, new_data.id_reader) == 0) return 0; // trùng mã độc giả
        prev = curr;
        curr = curr->next;
    }
    Reader *newreader = makeReader(new_data);
    if(newreader == NULL) return -1; // lỗi cấp phát bộ nhớ
    if(prev == NULL) *head = newreader; // danh sách rỗng thì thêm làm node đầu
    else prev->next = newreader; // nối vào sau node cuối cùng
    return 1; // thêm thành công
}

// 2.3.3. Hàm xóa độc giả theo mã độc giả
int deleteReader(Reader **head, char id_reader[]){
    if(*head == NULL) return 0; // danh sách rỗng
    Reader *curr = *head; // curr: node hiện tại đang xét
    Reader *prev = NULL;  // prev: node đứng ngay trước curr
    while(curr != NULL && strcmp(curr->data.id_reader, id_reader) != 0){
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL) return 0; // không tìm thấy độc giả
    if(curr->data.current_borrowed > 0) return -1; // trả về -1 nếu độc giả đang giữ sách chưa trả
    if(prev == NULL) *head = curr->next; // xóa độc giả ở đầu danh sách
    else prev->next = curr->next; // xóa độc giả ở giữa hoặc cuối danh sách
    free(curr); // giải phóng bộ nhớ
    return 1; // xóa thành công
}

// 2.3.4. Hàm cập nhật thông tin độc giả
int updateReader(Reader *head, char id_reader[], Reader_info updated_data){
    Reader *target = findReader(head, id_reader); // target: node độc giả cần sửa
    if(target == NULL) return 0; // không tìm thấy độc giả

    strcpy(updated_data.id_reader, target->data.id_reader); // giữ nguyên mã độc giả cũ
    updated_data.current_borrowed = target->data.current_borrowed; // giữ nguyên số sách đang mượn
    target->data = updated_data; // cập nhật thông tin mới
    return 1; // cập nhật thành công
}

// 2.4. Các hàm mượn và trả sách

// 2.4.1. Hàm mượn sách (b_info: borrow_info: thông tin mượn)
int BorrowBook(Book *Book_head, Reader *reader_head, Borrow **borrow_head, BorrowData b_info){
    Reader *r = findReader(reader_head, b_info.id_reader); // r: con trỏ trỏ tới độc giả mượn sách
    if(r == NULL) return -1; // trả về -1 nếu mã độc giả không tồn tại
    
    Book *b = findBook(Book_head, b_info.id_book); // b: con trỏ trỏ tới cuốn sách được mượn
    if(b == NULL) return -2; // trả về -2 nếu mã sách không tồn tại
    if(b->data.quantity <= 0) return -3; // trả về -3 nếu sách trong kho đã hết (số lượng = 0)

    Borrow *newborrow = makeBorrow(b_info); // tạo node phiếu mượn mới
    if(newborrow == NULL) return 0; // lỗi cấp phát bộ nhớ
    newborrow->next = *borrow_head; // chèn phiếu mượn vào đầu danh sách để đạt tốc độ nhanh nhất O(1)
    *borrow_head = newborrow; // cập nhật lại đầu danh sách mượn

    b->data.quantity--; // giảm số lượng sách tồn kho đi 1
    b->data.borrow_count++; // tăng tổng số lượt mượn của cuốn sách lên 1
    r->data.current_borrowed++; // tăng số lượng sách độc giả đang giữ lên 1
    return 1; // mượn sách thành công
}

// 2.4.2. Hàm trả sách
int ReturnBook(Book *Book_head, Reader *reader_head, Borrow *borrow_head, char id_reader[], char id_book[], char return_date[]){
    while(borrow_head != NULL){
        // tìm phiếu mượn khớp mã độc giả, mã sách và đang ở trạng thái chưa trả (status == 1)
        if(strcmp(borrow_head->data.id_reader, id_reader) == 0 &&
           strcmp(borrow_head->data.id_book, id_book) == 0 &&
           borrow_head->data.status == 1){
            
            borrow_head->data.status = 0; // đổi trạng thái phiếu sang đã trả (0)
            strcpy(borrow_head->data.return_date, return_date); // ghi nhận ngày trả sách

            Book *b = findBook(Book_head, id_book); // tìm cuốn sách vừa trả trong kho
            if(b != NULL) b->data.quantity++; // cộng trả lại 1 cuốn vào kho sách

            Reader *r = findReader(reader_head, id_reader); // tìm độc giả vừa trả sách
            if(r != NULL && r->data.current_borrowed > 0) r->data.current_borrowed--; // giảm số sách độc giả đang mượn đi 1
            return 1; // trả sách thành công
        }
        borrow_head = borrow_head->next;
    }
    return 0; // không tìm thấy phiếu đang mượn hợp lệ
}

// 2.5. Các hàm sắp xếp, tìm kiếm và thống kê

// 2.5.1. Hàm sắp xếp sách bằng Sắp xếp chọn (Selection Sort)
// mode (chế độ sắp xếp): 1 = theo tên sách, 2 = theo năm xuất bản, 3 = theo số lượng
void selectionSortBook(Book *head, int mode){
    for(Book *i = head; i != NULL && i->next != NULL; i = i->next){
        Book *minBook = i; // minBook: con trỏ lưu địa chỉ node có giá trị nhỏ nhất (giả sử ban đầu là i)
        for(Book *j = i->next; j != NULL; j = j->next){
            int check = 0; // check: biến cờ kiểm tra xem node j có nhỏ hơn minBook không (1: có, 0: không)
            if(mode == 1) check = (strcmp(j->data.name_book, minBook->data.name_book) < 0); // so sánh tên từ A-Z
            else if(mode == 2) check = (j->data.year_publish < minBook->data.year_publish); // so sánh năm xuất bản tăng dần
            else if(mode == 3) check = (j->data.quantity < minBook->data.quantity); // so sánh số lượng tăng dần
            if(check) minBook = j; // nếu node j nhỏ hơn thì cập nhật minBook trỏ vào j
        }
        if(minBook != i){
            // tmp: biến tạm dùng để hoán đổi dữ liệu giữa node i và node minBook
            Book_info tmp = i->data;
            i->data = minBook->data;
            minBook->data = tmp;
        }
    }
}

// 2.5.2. Hàm tìm kiếm sách theo tên bằng giải thuật Sắp xếp chọn
Book *searchBook(Book *head, char exact_name[]){
    selectionSortBook(head, 1); // bước 1: sắp xếp danh sách sách theo tên từ A-Z
    while(head != NULL){
        // cmp: lưu kết quả so sánh tên sách hiện tại với tên cần tìm (exact_name)
        int cmp = strcmp(head->data.name_book, exact_name);
        if(cmp == 0) return head; // cmp == 0 nghĩa là 2 tên giống hệt nhau -> trả về node sách tìm thấy
        if(cmp > 0) break; // cmp > 0 nghĩa là tên sách trên kệ đã vượt qua chữ cái cần tìm -> dừng sớm vòng lặp
        head = head->next;
    }
    return NULL; // không tìm thấy
}

// 2.5.3. Hàm tìm số lượng sách đang mượn lớn nhất trong danh sách độc giả
int maxReaderBorrow(Reader *head){
    int max = 0; // biến lưu kỷ lục số sách đang mượn lớn nhất
    while(head != NULL){
        if(head->data.current_borrowed > max) max = head->data.current_borrowed; // cập nhật giá trị lớn nhất
        head = head->next;
    }
    return max; // trả về số lượng lớn nhất
}

// 2.5.4. Hàm tìm số lượt được mượn lớn nhất trong danh sách sách
int maxBookBorrow(Book *head){
    int max = 0; // biến lưu kỷ lục số lượt mượn lớn nhất
    while(head != NULL){
        if(head->data.borrow_count > max) max = head->data.borrow_count; // cập nhật giá trị lớn nhất
        head = head->next;
    }
    return max; // trả về số lượt lớn nhất
}

// 2.5.5. Hàm giải phóng toàn bộ bộ nhớ cấp phát động khi thoát chương trình
// b_head: đầu DS sách | r_head: đầu DS độc giả | m_head: đầu DS mượn trả | tmp: con trỏ tạm giữ node cần xóa
void freeAll(Book **b_head, Reader **r_head, Borrow **m_head){
    while(*b_head != NULL){ Book *tmp = *b_head; *b_head = (*b_head)->next; free(tmp); } // giải phóng DS sách
    while(*r_head != NULL){ Reader *tmp = *r_head; *r_head = (*r_head)->next; free(tmp); } // giải phóng DS độc giả
    while(*m_head != NULL){ Borrow *tmp = *m_head; *m_head = (*m_head)->next; free(tmp); } // giải phóng DS mượn trả
}

// 2.6. Hàm khởi tạo dữ liệu mẫu (10 sách, 5 độc giả, 4 giao dịch mượn/trả)
void initSampleData(Book **book_head, Reader **reader_head, Borrow **borrow_head){
    // 1. Nạp danh sách 10 cuốn sách mẫu
    Book_info b[] = {
        {"B01", "Nha gia kim", "Paulo Coelho", "NXB Hoi Nha Van", 1988, 5},
        {"B02", "Cuon theo chieu gio", "Margaret Mitchell", "NXB Van Hoc", 1936, 3},
        {"B03", "Doi gio hu", "Emily Bronte", "NXB Van Hoc", 1847, 2},
        {"B04", "Chua ruoi", "William Golding", "NXB Faber & Faber", 1954, 4},
        {"B05", "Tren sa mac va trong rung tham", "Henryk Sienkiewicz", "NXB Kim Dong", 1911, 0}, // SL = 0 để test tình trạng hết sách
        {"B06", "Data Structures & Algorithms", "Michael T. Goodrich", "Wiley", 2011, 6},
        {"B07", "Cau truc du lieu va giai thuat", "Nguyen Duc Nghia", "NXB DH Bach Khoa", 2003, 7},
        {"B08", "Doi ngan dung ngu dai", "Robin Sharma", "NXB Tre", 2007, 8},
        {"B09", "Campbell Biology", "Neil A. Campbell", "Pearson", 2020, 4},
        {"B10", "Hoa hoc dai cuong", "Vu Dang Do", "NXB Giao Duc", 2018, 5}
    };
    for(int i = 0; i < 10; i++) addBook(book_head, b[i]); // thêm lần lượt 10 cuốn vào danh sách sách

    // 2. Nạp danh sách 5 độc giả mẫu
    Reader_info r[] = {
        {"DG01", "Ngo Quan Duc", "CNTT1-K15", "0912345678"},
        {"DG02", "Le Tuan Dat", "CNTT2-K15", "0987654321"},
        {"DG03", "Dao Duy Thanh", "KTPM-K15", "0901234567"},
        {"DG04", "Pham Tuyet Nhinh", "KHMT-K15", "0983576478"},
        {"DG05", "Nguyen Mai Linh", "TTNT-K17", "0901884776"}
    };
    for(int i = 0; i < 5; i++) addReader(reader_head, r[i]); // thêm lần lượt 5 độc giả vào danh sách độc giả

    // 3. Tạo một số lượt mượn/trả mẫu để kiểm thử thống kê và lịch sử
    // - DG01 mượn 2 cuốn: B01 và B06 (trở thành độc giả đang giữ nhiều sách nhất)
    BorrowData m1 = {"DG01", "B01", "10/10/2026"};
    BorrowData m2 = {"DG01", "B06", "12/10/2026"};
    BorrowBook(*book_head, *reader_head, borrow_head, m1); 
    BorrowBook(*book_head, *reader_head, borrow_head, m2); 

    // - DG02 mượn B01 rồi đã trả 
    BorrowData m3 = {"DG02", "B01", "01/10/2026"};
    BorrowBook(*book_head, *reader_head, borrow_head, m3);
    ReturnBook(*book_head, *reader_head, *borrow_head, "DG02", "B01", "08/10/2026"); 

    // - DG03 mượn B07
    BorrowData m4 = {"DG03", "B07", "15/10/2026"};
    BorrowBook(*book_head, *reader_head, borrow_head, m4); 
}

// 3. CÁC HÀM NHẬP XUẤT VÀ MENU CON 

// 3.1. Hàm nhập chuỗi an toàn
// msg(message): câu thông báo in ra màn hình | str: mảng lưu chuỗi nhập vào | size: độ dài tối đa của mảng str
void inputStr(char msg[], char str[], int size){
    printf("%s", msg); // in câu thông báo nhắc người dùng
    fgets(str, size, stdin); // đọc cả dòng chuỗi có dấu cách từ bàn phím (stdin)
    str[strlen(str) - 1] = '\0'; // strlen(str) - 1 là vị trí ký tự Enter ('\n') ở cuối chuỗi -> gán bằng '\0' để xóa đi
}

// 3.2. Hàm in bảng danh sách sách
void printBooks(Book *head){
    if(head == NULL){ printf("-> Danh sach sach dang trong!\n"); return; }
    // %-10s: dành ra 10 ô ký tự và canh lề trái cho chuỗi | %-6d: dành 6 ô canh lề trái cho số nguyên
    printf("\n%-10s | %-30s | %-20s | %-18s | %-6s | %-6s | %-8s\n",
           "Ma Sach", "Ten Sach", "Tac Gia", "NXB", "Nam XB", "SL Kho", "Luot Muon");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    while(head != NULL){
        printf("%-10s | %-30s | %-20s | %-18s | %-6d | %-6d | %-8d\n",
               head->data.id_book, head->data.name_book, head->data.author,
               head->data.publisher, head->data.year_publish, head->data.quantity, head->data.borrow_count);
        head = head->next;
    }
}

// 3.3. Hàm in bảng danh sách độc giả 
void printReaders(Reader *head){
    if(head == NULL){ printf("-> Danh sach doc gia dang trong!\n"); return; }
    printf("\n%-12s | %-25s | %-12s | %-15s | %-12s\n",
           "Ma Doc Gia", "Ho Ten", "Lop", "So Dien Thoai", "Dang Muon");
    printf("------------------------------------------------------------------------------------\n");
    while(head != NULL){
        printf("%-12s | %-25s | %-12s | %-15s | %-12d\n",
               head->data.id_reader, head->data.name_reader, head->data.class_name,
               head->data.phone, head->data.current_borrowed);
        head = head->next;
    }
}

// 3.4. Menu con quản lý sách (Thêm / Xóa / Sửa / In)
void menuBook(Book **Book_head){
    int sub; // sub(sub-menu): biến lưu lựa chọn trong menu con (1, 2, 3 hoặc 4)
    printf("  [1] Them sach  [2] Xoa sach  [3] Sua sach  [4] In DS sach: ");
    if(scanf("%d", &sub) != 1){ while(getchar() != '\n'); return; } // nếu nhập chữ (scanf != 1) thì xóa bộ đệm và thoát menu con
    getchar(); // xóa phím Enter thừa trong bộ đệm

    if(sub == 1){
        Book_info b; // b (book): biến cấu trúc tạm để lưu thông tin sách người dùng nhập
        inputStr("  Nhap ma sach: ", b.id_book, sizeof(b.id_book));
        inputStr("  Nhap ten sach: ", b.name_book, sizeof(b.name_book));
        inputStr("  Nhap tac gia: ", b.author, sizeof(b.author));
        inputStr("  Nhap NXB: ", b.publisher, sizeof(b.publisher));
        printf("  Nhap nam XB va so luong: ");
        scanf("%d %d", &b.year_publish, &b.quantity); getchar();
        if(addBook(Book_head, b) == 1) printf("-> Them sach thanh cong!\n");
        else printf("-> [Loi] Ma sach da ton tai!\n");
    }
    else if(sub == 2){
        char id[20]; // id: mảng lưu mã sách cần xóa
        inputStr("  Nhap ma sach can xoa: ", id, sizeof(id));
        if(deleteBook(Book_head, id) == 1) printf("-> Xoa sach thanh cong!\n");
        else printf("-> [Loi] Khong tim thay ma sach!\n");
    }
    else if(sub == 3){
        Book_info b;
        inputStr("  Nhap ma sach can sua: ", b.id_book, sizeof(b.id_book));
        inputStr("  Nhap ten sach moi: ", b.name_book, sizeof(b.name_book));
        inputStr("  Nhap tac gia moi: ", b.author, sizeof(b.author));
        inputStr("  Nhap NXB moi: ", b.publisher, sizeof(b.publisher));
        printf("  Nhap nam XB va so luong moi: ");
        scanf("%d %d", &b.year_publish, &b.quantity); getchar();
        if(updateBook(*Book_head, b.id_book, b) == 1) printf("-> Sua thong tin sach thanh cong!\n");
        else printf("-> [Loi] Khong tim thay ma sach!\n");
    }
    else if(sub == 4) printBooks(*Book_head);
}

// 3.5. Menu con quản lý độc giả (Thêm / Xóa / Sửa / In)
void menuReader(Reader **reader_head){
    int sub; // sub(sub-menu): biến lưu lựa chọn trong menu con độc giả
    printf("  [1] Them DG  [2] Xoa DG  [3] Sua DG  [4] In DS doc gia: ");
    if(scanf("%d", &sub) != 1){ while(getchar() != '\n'); return; } // nếu nhập sai kiểu số thì xóa bộ đệm và thoát
    getchar(); // xóa phím Enter thừa trong bộ đệm

    if(sub == 1){
        Reader_info r; // r(reader): biến cấu trúc lưu thông tin độc giả mới nhập
        inputStr("  Nhap ma doc gia: ", r.id_reader, sizeof(r.id_reader));
        inputStr("  Nhap ho ten: ", r.name_reader, sizeof(r.name_reader));
        inputStr("  Nhap lop: ", r.class_name, sizeof(r.class_name));
        inputStr("  Nhap SDT: ", r.phone, sizeof(r.phone));
        if(addReader(reader_head, r) == 1) printf("-> Them doc gia thanh cong!\n");
        else printf("-> [Loi] Ma doc gia da ton tai!\n");
    }
    else if(sub == 2){
        char id[20];
        inputStr("  Nhap ma doc gia can xoa: ", id, sizeof(id));
        int res = deleteReader(reader_head, id); // res: nhận mã kết quả trả về từ hàm xóa (1, -1 hoặc 0)
        if(res == 1) printf("-> Xoa doc gia thanh cong!\n");
        else if(res == -1) printf("-> [Loi] Doc gia dang muon sach, khong duoc xoa!\n");
        else printf("-> [Loi] Khong tim thay ma doc gia!\n");
    }
    else if(sub == 3){
        Reader_info r;
        inputStr("  Nhap ma doc gia can sua: ", r.id_reader, sizeof(r.id_reader));
        inputStr("  Nhap ho ten moi: ", r.name_reader, sizeof(r.name_reader));
        inputStr("  Nhap lop moi: ", r.class_name, sizeof(r.class_name));
        inputStr("  Nhap SDT moi: ", r.phone, sizeof(r.phone));
        if(updateReader(*reader_head, r.id_reader, r) == 1) printf("-> Sua thong tin doc gia thanh cong!\n");
        else printf("-> [Loi] Khong tim thay ma doc gia!\n");
    }
    else if(sub == 4) printReaders(*reader_head);
}

// 4. HÀM MAIN ĐIỀU KHIỂN CHƯƠNG TRÌNH 

int main(){
    Book *book_head = NULL;       // con trỏ quản lý đầu danh sách sách (ban đầu rỗng)
    Reader *reader_head = NULL;   // con trỏ quản lý đầu danh sách độc giả (ban đầu rỗng)
    Borrow *borrow_head = NULL;   // con trỏ quản lý đầu danh sách phiếu mượn (ban đầu rỗng)
    int choice;                   // choice: biến lưu lựa chọn chức năng ở menu chính (từ 0 đến 11)

    // Nạp sẵn dữ liệu ngay khi khởi động chương trình
    initSampleData(&book_head, &reader_head, &borrow_head);
    //printf("-> Da khoi tao 10 cuon sach, 5 doc gia va lich su muon mau!\n"");

    while(1){ // vòng lặp vô hạn giữ chương trình chạy liên tục cho đến khi chọn 0 (break)
        printf("\n==================== HE THONG QUAN LY THU VIEN ====================\n");
        printf(" 1. Them / Xoa / Sua Sach          7. Tra cuu lich su muon\n");
        printf(" 2. Them / Xoa / Sua Doc gia       8. Doc gia muon nhieu sach nhat\n");
        printf(" 3. Muon sach                      9. Sach duoc muon nhieu nhat\n");
        printf(" 4. Tra sach                      10. Sap xep sach\n");
        printf(" 5. Kiem tra sach con hay het     11. Tim kiem sach\n");
        printf(" 6. Tra cuu sach                   0. Thoat chuong trinh\n");
        printf("===================================================================\n");
        printf("Nhap lua chon: ");

        if(scanf("%d", &choice) != 1){ // nếu người dùng gõ chữ cái khiến scanf không đọc được số nguyên (trả về != 1)
            while(getchar() != '\n'); // đọc và vứt bỏ toàn bộ các ký tự chữ bị kẹt trong bộ đệm bàn phím
            printf("-> Vui long nhap so!\n");
            continue; // quay lại đầu vòng lặp while(1) để in lại menu
        }
        getchar(); // xóa ký tự Enter ('\n') còn sót lại sau khi nhập số choice

        if(choice == 0){
            freeAll(&book_head, &reader_head, &borrow_head); // giải phóng toàn bộ bộ nhớ động trước khi kết thúc
            printf("-> Da giai phong bo nho va thoat chuong trinh!\n");
            break; // thoát khỏi vòng lặp while(1)
        }
        else if(choice == 1) menuBook(&book_head); // yêu cầu 1: thêm/xóa/sửa sách
        else if(choice == 2) menuReader(&reader_head); // yêu cầu 2: thêm/xóa/sửa độc giả
        else if(choice == 3){ // yêu cầu 3: mượn sách
            BorrowData bd; // bd(borrow data): biến cấu trúc tạm lưu thông tin mượn sách
            inputStr("  Nhap ma doc gia: ", bd.id_reader, sizeof(bd.id_reader));
            inputStr("  Nhap ma sach muon: ", bd.id_book, sizeof(bd.id_book));
            inputStr("  Nhap ngay muon (dd/mm/yyyy): ", bd.borrow_date, sizeof(bd.borrow_date));
            int res = BorrowBook(book_head, reader_head, &borrow_head, bd); // res: mã kết quả mượn sách
            if(res == 1) printf("-> Muon sach thanh cong!\n");
            else if(res == -1) printf("-> [Loi] Khong tim thay ma doc gia!\n");
            else if(res == -2) printf("-> [Loi] Khong tim thay ma sach!\n");
            else if(res == -3) printf("-> [Loi] Sach trong kho da het!\n");
        }
        else if(choice == 4){ // yêu cầu 4: trả sách
            // id_r: mã độc giả (id_reader) | id_b: mã sách (id_book) | r_date: ngày trả (return_date)
            char id_r[20], id_b[20], r_date[15];
            inputStr("  Nhap ma doc gia: ", id_r, sizeof(id_r));
            inputStr("  Nhap ma sach tra: ", id_b, sizeof(id_b));
            inputStr("  Nhap ngay tra (dd/mm/yyyy): ", r_date, sizeof(r_date));
            if(ReturnBook(book_head, reader_head, borrow_head, id_r, id_b, r_date) == 1)
                printf("-> Tra sach thanh cong!\n");
            else printf("-> [Loi] Khong tim thay phieu dang muon hop le!\n");
        }
        else if(choice == 5){ // yêu cầu 5: kiểm tra sách còn hay hết
            char id[20]; // id: mã cuốn sách cần kiểm tra tồn kho
            inputStr("  Nhap ma sach can kiem tra: ", id, sizeof(id));
            int sl = checkBookStock(book_head, id); // sl: nhận số lượng sách còn trong kho
            if(sl == -1) printf("-> Khong tim thay ma sach!\n");
            else if(sl == 0) printf("-> Tinh trang: HET SACH (0 cuon)\n");
            else printf("-> Tinh trang: CON SACH (Con %d cuon trong kho)\n", sl);
        }
        else if(choice == 6){ // yêu cầu 6: tra cứu sách gần đúng theo mã, tên hoặc tác giả
            char kw[100]; // kw(keyword): biến lưu từ khóa tìm kiếm người dùng nhập vào
            int found = 0; // found: biến cờ đánh dấu kết quả (0 = chưa tìm thấy, 1 = đã tìm thấy ít nhất 1 cuốn)
            inputStr("  Nhap tu khoa can tim (Ma / Ten / Tac gia): ", kw, sizeof(kw));
            // dùng con trỏ p chạy duyệt từ đầu danh sách sách (book_head) đến cuối (NULL)
            for(Book *p = book_head; p != NULL; p = p->next){
                // hàm strstr(chuỗi_lớn, kw) kiểm tra xem từ khóa kw có nằm bên trong Mã sách, Tên sách hoặc Tác giả không
                if(strstr(p->data.id_book, kw) || strstr(p->data.name_book, kw) || strstr(p->data.author, kw)){
                    printf("  + [%s] %s - TG: %s - NXB: %s (Kho: %d)\n",
                           p->data.id_book, p->data.name_book, p->data.author, p->data.publisher, p->data.quantity);
                    found = 1; // bật cờ found = 1 vì đã tìm thấy sách khớp từ khóa
                }
            }
            if(!found) printf("-> Khong tim thay cuon sach nao phu hop!\n"); // !found nghĩa là found == 0 (không tìm thấy)
        }
        else if(choice == 7){ // yêu cầu 7: tra cứu lịch sử mượn trả
            if(borrow_head == NULL) printf("-> Chua co lich su muon/tra sach!\n");
            else{
                printf("\n%-12s | %-10s | %-12s | %-12s | %-12s\n", "Ma Doc Gia", "Ma Sach", "Ngay Muon", "Ngay Tra", "Trang Thai");
                printf("----------------------------------------------------------------------\n");
               // dùng con trỏ p duyệt qua từng phiếu mượn trong danh sách borrow_head
                for(Borrow *p = borrow_head; p != NULL; p = p->next){
                    char *trang_thai;
                    if(p->data.status == 1)  trang_thai = "Dang muon"; // nếu status bằng 1 là đang mượn
                    else trang_thai = "Da tra";     // ngược lại là đã trả sách
                printf("%-12s | %-10s | %-12s | %-12s | %-12s\n", p->data.id_reader, p->data.id_book, p->data.borrow_date,p->data.return_date, trang_thai);
                }
            }
        }
        else if(choice == 8){ // yêu cầu 8: xác định độc giả đang mượn nhiều sách nhất
            int max_r = maxReaderBorrow(reader_head); // max_r (max reader): số lượng sách đang mượn cao nhất
            if(max_r == 0) printf("-> Hien khong co doc gia nao dang muon sach!\n");
            else{
                printf("-> Doc gia dang muon nhieu sach nhat (%d cuon):\n", max_r);
                // dùng con trỏ p duyệt tìm và in ra tất cả độc giả có số sách đang mượn bằng kỷ lục max_r
                for(Reader *p = reader_head; p != NULL; p = p->next){
                    if(p->data.current_borrowed == max_r)
                        printf("   + [%s] %s - Lop: %s - SDT: %s\n",
                               p->data.id_reader, p->data.name_reader, p->data.class_name, p->data.phone);
                }
            }
        }
        else if(choice == 9){ // yêu cầu 9: tìm sách được mượn nhiều nhất
            int max_b = maxBookBorrow(book_head); // max_b (max book): số lượt được mượn cao nhất của sách
            if(max_b == 0) printf("-> Chua co cuon sach nao duoc muon!\n");
            else{
                printf("-> Sach duoc muon nhieu nhat (%d luot):\n", max_b);
                // dùng con trỏ p duyệt tìm và in ra tất cả các cuốn sách có số lượt mượn bằng max_b
                for(Book *p = book_head; p != NULL; p = p->next){
                    if(p->data.borrow_count == max_b)
                        printf("   + [%s] %s - Tac gia: %s\n",
                               p->data.id_book, p->data.name_book, p->data.author);
                }
            }
        }
        else if(choice == 10){ // yêu cầu 10: sắp xếp sách theo tên, năm xuất bản, số lượng
            int mode; // mode: tiêu chí sắp xếp do người dùng chọn (1, 2 hoặc 3)
            printf("  Chon tieu chi sap xep (1: Ten sach, 2: Nam XB, 3: So luong): ");
            scanf("%d", &mode); getchar();
            selectionSortBook(book_head, mode);
            printf("-> Da sap xep danh sach sach thanh cong!\n");
            printBooks(book_head); // in bảng sách ra màn hình sau khi sắp xếp xong
        }
        else if(choice == 11){ // yêu cầu 11: tìm kiếm sách bằng giải thuật sắp xếp chọn
            char name[100]; // name: mảng lưu tên cuốn sách cần tìm
            inputStr("  Nhap ten sach can tim: ", name, sizeof(name));
            Book *found = searchBook(book_head, name); // found: con trỏ nhận địa chỉ node sách tìm được (hoặc NULL nếu không thấy)
            if(found != NULL){
                printf("-> Tim thay: [%s] %s - TG: %s - Nam XB: %d - Con: %d cuon\n",
                       found->data.id_book, found->data.name_book, found->data.author,
                       found->data.year_publish, found->data.quantity);
            }
            else printf("-> Khong tim thay sach co ten '%s'!\n", name);
        }
        else printf("-> Lua chon khong hop le!\n");
    }
    return 0;
}