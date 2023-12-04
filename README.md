# PROJECT DESIGN PATTERN 

------------------

## RULES FOR PROJECT DESIGN PATTERN

### 1. Requirement

Each group choose two patterns:

* A structural pattern : Adapter
* A behavioral pattern : Mediator

Present the patterns and record your presentation into video (duration: 10’ - 30’)

### 2. Submission

Save your project into a folder on your cloud (google drive or onedrive). The folder includes:

* **Slide:** [group]-[mssvs].pptx or pdf
* **Report:** [group]-[mssvs].docx or pdf
* **Video:** [group]-[mssvs].mp4
* **Source code**

Group leader submit the link to the folder through Moodle.

### 3. Assessment

| Item    | Ratio |
| ------- | ----- |
| Content |  50%  |
| Video   |  25%  |
| Slide   |  25%  |

------------------

## LECTURE OF PROJECT DESSIGN PATTERN

### Structural Design Pattern: Adapter

#### 1. Definition

**Adapter** là mẫu thiết kế cấu trúc cho phép các đối tượng có giao diện không tương thích cộng tác. (**Adapter** is a *structural* design pattern that allows objects with incompatible interfaces to collaborate.)

<center><img src = https://refactoring.guru/images/patterns/content/adapter/adapter-en.png></center>

#### 2. Problem

**Ví dụ 1:**
Hãy tưởng tượng bạn đang tạo một ***ứng dụng*** theo dõi thị trường chứng khoán. Ứng dụng tải xuống dữ liệu chứng khoán từ nhiều nguồn ở định dạng XML, sau đó hiển thị các biểu đồ và sơ đồ đẹp mắt cho người dùng.

<center><img src = https://refactoring.guru/images/patterns/diagrams/adapter/problem-en-2x.png></center>

Tại một thời điểm nào đó, bạn quyết định cải thiện ứng dụng bằng cách tích hợp thư viện phân tích thông minh của bên thứ 3. Nhưng có một nhược điểm: thư viện phân tích chỉ hoạt động với dữ liệu ở định dạng JSON. Bạn có thể thay đổi thư viện để hoạt động với XML. Tuy nhiên, điều này có thể phá vỡ cấu trúc một số mã hiện có dựa trên thư viện. Và tệ hơn, bạn có thể không có quyền truy cập vào mã nguồn của thư viện ngay từ đầu, khiến phương pháp này không thể thực hiện được.

**Ví dụ 2:**
Trong thực tế, có rất nhiều loại phích cắm điện với đa dạng chủng loại và thiết kế. Tùy vào đất nước và mục đích sử dụng của từng cá nhân và tổ chức khác nhau. Ở Việt Nam thường sử dụng cách loại phích cắm điện có 2 chân để phù hợp với ổ điện có hai lỗ cắm. Tuy nhiên, nếu một ngày bạn đi du lịch qua các nước Mỹ Âu vả bạn nhận ra tại đây mọi người đều sử dụng các loại phích cắm điện 3 chân và ổ cắm điện cũng không phù hợp với loại bạn đang dùng ở Việt Nam và trong hoàn cảnh đó chiếc Laptop của bạn đang cần sạc Pin gấp thì bạn nên xử lý như thế nào?

<center><img src = https://refactoring.guru/images/patterns/content/adapter/adapter-comic-1-en.png></center>

#### 3. Solution

Bạn có thể tạo một bộ chuyển đổi (***adapter***). Đây là một đối tượng đặc biệt có chức năng chuyển đổi giao diện của một đối tượng để đối tượng khác có thể hiểu được.

Bộ ***adapter*** bao bọc (wraps) một trong các đối tượng để che giấu sự phức tạp của quá trình chuyển đổi diễn ra ở hậu trường. Đối tượng được bao bọc thậm chí không nhận biết được bộ chuyển đổi. Ví dụ: bạn có thể bao bọc một đối tượng hoạt động theo đơn vị mét và kilômét bằng một bộ chuyển đổi có khả năng chuyển đổi tất cả dữ liệu sang các đơn vị đo lường Anh như feet và dặm.

Bộ ***adapter*** không chỉ có thể chuyển đổi dữ liệu sang nhiều định dạng khác nhau mà còn có thể giúp các đối tượng có giao diện khác nhau cộng tác với nhau. Đây là cách nó hoạt động:

1. Bộ ***adapter*** có giao diện tương thích với một trong các đối tượng hiện có.
2. Sử dụng giao diện này, đối tượng hiện có có thể gọi các phương thức của bộ điều hợp một cách an toàn.
3. Khi nhận được cuộc gọi, bộ ***adapter*** sẽ chuyển yêu cầu đến đối tượng thứ hai nhưng theo định dạng và thứ tự mà đối tượng thứ hai mong đợi.

Đôi khi, thậm chí có thể tạo bộ adapter hai chiều có thể chuyển đổi cuộc gọi theo cả hai hướng.

<center><img src =https://refactoring.guru/images/patterns/diagrams/adapter/solution-en-2x.png> </center>

Hãy quay lại ứng dụng thị trường chứng khoán trong ví dụ 1 . Để giải quyết vấn đề nan giải về các định dạng không tương thích, ta có thể tạo bộ chuyển đổi XML sang JSON cho mọi lớp của thư viện phân tích mà mã của ta làm việc trực tiếp. Sau đó, ta điều chỉnh mã của mình để chỉ giao tiếp với thư viện thông qua các bộ ***adapter*** này. Khi bộ điều hợp nhận được lệnh gọi, nó sẽ dịch dữ liệu XML đến thành cấu trúc JSON và chuyển lệnh gọi đó đến các phương thức thích hợp của đối tượng phân tích được bao bọc.

#### 4. Structure

##### 4.1. Object Adapter

Việc triển khai này sử dụng nguyên lý thành phần đối tượng: bộ ***adapter*** triển khai giao diện của một đối tượng và bao bọc đối tượng kia. Nó có thể được thực hiện bằng tất cả các ngôn ngữ lập trình phổ biến.

<center><img src=https://refactoring.guru/images/patterns/diagrams/adapter/structure-object-adapter-indexed.png></center>

1. ***Client*** là lớp chứa logic nghiệp vụ (*business logic*) hiện có của chương trình.
2. ***Client Interface*** là giao diện của ***client*** mà bộ ***adapter*** sẽ triển khai. Nó mô tả một giao thức mà các lớp khác phải tuân theo để có thể cộng tác với code của Client.
3. ***Service*** là một số lớp hữu ích (thường là bên thứ 3 hoặc kế thừa). ***Client*** không thể sử dụng trực tiếp lớp này vì nó có giao diện không tương thích.
4. ***Adapter*** là một lớp có thể hoạt động với cả ***Client*** và ***Service*** : nó triển khai ***Client Interfaces*** trong khi bao bọc đối tượng ***Service***. ***Adapter*** nhận lời gọi từ máy khách thông qua giao diện máy khách và chuyển chúng thành cuộc gọi đến đối tượng dịch vụ được bao bọc theo định dạng mà nó có thể hiểu được.
5. Code của ***Client*** không được ghép nối với lớp ***Adapter*** cụ thể miễn là nó hoạt động thông qua giao diện ***Client***. Nhờ vậy, bạn có thể đưa vào chương trình nhiều lớp ***Adapter*** khác nhau mà không cần thay đổi code của ***Client*** (Không vi phạm code của ***Client***  hiện có). Điều này có thể hữu ích khi giao diện của lớp ***Service*** bị thay đổi hoặc thay thế: bạn chỉ có thể tạo một lớp ***Adapter*** mới mà không cần thay đổi code của ***Client***.

##### 4.2. Class Adapter

Việc triển khai này sử dụng tính kế thừa: **Adapter** kế thừa giao diện từ cả hai đối tượng cùng một lúc. Lưu ý rằng phương pháp này chỉ có thể được triển khai bằng các ngôn ngữ lập trình hỗ trợ đa kế thừa, chẳng hạn như C++.

<center> <img src = https://refactoring.guru/images/patterns/diagrams/adapter/structure-class-adapter-indexed.png> </center>

Bộ điều hợp lớp không cần bọc bất kỳ đối tượng nào vì nó kế thừa các hành vi từ cả máy khách và dịch vụ. Sự thích ứng xảy ra trong các phương thức được ghi đè. Bộ điều hợp kết quả có thể được sử dụng thay cho lớp máy khách hiện có.

#### 5. Application

* Sử dụng lớp Adapter khi bạn muốn sử dụng một số lớp hiện có nhưng giao diện của nó không tương thích với phần còn lại của mã.
  
  * Mẫu ***Adapter*** cho phép bạn tạo một lớp middle-layer đóng vai trò là bộ dịch giữa code của bạn và lớp kế thừa, lớp của bên thứ 3 hoặc bất kỳ lớp nào khác có giao diện lạ

* Sử dụng mẫu này khi bạn muốn sử dụng lại một số lớp con hiện có thiếu một số chức năng phổ biến không thể thêm vào lớp cha.

  * Bạn có thể mở rộng từng lớp con và đưa chức năng còn thiếu vào các lớp con mới. Tuy nhiên, bạn sẽ cần phải sao chép mã trên tất cả các lớp mới này, điều này có vẻ rất tệ.
  * Giải pháp tinh tế hon nhiều là có thể đặt các chức năng này vào một lớp ***Adapter*** đơn lẻ. Bây giờ các lớp con có thể kế thừa từ lớp ***Adapter*** và có tất cả các chức năng mà chúng cần. Khi đó, bạn sẽ đóng gói các đối tượng có tính năng bị thiếu bên trong ***Adapter***, thu được các tính năng cần thiết một cách linh hoạt. Để tính năng này hoạt động, các lớp mục tiêu phải có giao diện chung và adapter's field phải tuân theo giao diện đó. Cách tiếp cận này trông rất giống với *Đecorator Pattern*. Tuy nhiên, ***Adapter*** thường cung cấp một giao diện khác so với các lớp mục tiêu. Nó cũng có thể là một lớp trung gian đơn giản không có chức năng bổ sung nào. Điều này có thể hữu ích khi bạn muốn tạo một số lớp con của một lớp không thể mở rộng (ví dụ: các lớp của bên thứ 3).
  * Mẫu ***Adapter*** cho phép bạn tạo một lớp trung gian bổ sung để bao bọc các lớp không thể mở rộng.

#### 6. How to Implement

1. Đảm bảo rằng bạn có ít nhất hai lớp có giao diện không tương thích:

    * Một lớp ***Service*** hữu ích là lớp bạn không thê thay đổi (thường là lớp của bên thứ 3 hoặc lớp kế thừa hoặc với nhiều phụ thuộc hiện có).
    * Một hay một số lớp ***Client*** rằng sẽ lấy lợi ích từ việc sử dụng lớp ***Service***.

2. Khai báo giao diện ***Client*** và mô tả các phương thức mà ***Client*** sử dụng để tương tác với ***Service***.

3. Tạo lớp ***Adapter*** và làm cho nó triển khai giao diện ***Client***. Bây giờ, chúng ta sẽ để trống tất cả các methods. Để ***Adapter*** có thể làm việc, nó phải có một trường để lưu trữ tham chiếu đến một đối tượng ***Service***. Thường thì ***Adapter*** nhận đối tượng ***Service*** thông qua tham số của phương thức khởi tạo của nó.

4. Thêm một field vào lớp ***Adapter*** để lưu trữ tham chiếu đến một đối tượng ***Service***. Thường thì ***Adapter*** nhận đối tượng ***Service*** thông qua tham số của phương thức khởi tạo của nó. Cách thực hành phổ biến là khởi tạo field này thông qua constructor của ***Adapter***, nhưng thỉnh thoảng nó có thể tiện lợi hơn để chuyển nó tới lớp ***Adapter*** khi gọi methods của nó.

5. Triển khai lần lượt tất cả các methods của ***Client Interface*** trong class ***Adapter***. Class ***Adapter*** sẽ ủy quyền hầu hết công việc thực sự cho đối tượng ***Service***, chỉ xử lý việc chuyển đổi định dạng dữ liệu hoặc giao diện.

6. Các clients nên sử dụng ***Adapter*** thông qua ***Client Interface***. Điều này sẽ cho phép bạn thay đổi hoặc mở rộng ***Adapter*** mà không làm thay đổi code của ***Client***.

#### 7. Pros and Cons

|Advantages|Disadvantages|
|----------|-------------|
|*Single Responsibility Principle*. Bạn có thể tách giao diện hoặc mã chuyển đổi dữ liệu khỏi logic nghiệp vụ chính của chương trình.|Độ phức tạp tổng thể của mã tăng lên vì bạn cần giới thiệu một tập hợp các giao diện và lớp mới. Đôi khi, việc thay đổi lớp dịch vụ sao cho phù hợp với phần còn lại của mã sẽ đơn giản hơn.|
|*Open/Closed Principle*.Bạn có thể đưa các loại ***Adapter*** mới vào chương trình mà không vi phạm code của client hiện có, miễn là chúng hoạt động với các ***Adapters*** thông qua ***Client Interface***.||

#### 8. Relations with Other Patterns

* `Bridge Pattern` thường được thiết kế trước, cho phép bạn phát triển các phần của ứng dụng độc lập với nhau. Mặt khác, `Adapter Pattern` thường được sử dụng với một ứng dụng hiện có để làm cho một số lớp không tương thích hoạt động tốt với nhau.
* `Adapter Pattern` cung cấp một giao diện khác biệt hoàn toàn để truy cập một đối tượng hiện có. Mặt khác, với `Decorator Pattern`, giao diện vẫn giữ nguyên hoặc được mở rộng. Ngoài ra, `Decorator Pattern` còn hỗ trợ thành phần đệ quy, điều này không thể thực hiện được khi bạn sử dụng `Adapter Pattern`.
* Với `Adapter Pattern`, bạn truy cập một đối tượng hiện có thông qua giao diện khác. Với `Proxy Pattern` thì giao diện vẫn giữ nguyên. Với `Decorator Pattern`, bạn truy cập đối tượng thông qua giao diện nâng cao.
* `Facade Pattern` xác định giao diện mới cho các đối tượng hiện có, trong khi `Adapter Pattern` cố gắng làm cho giao diện hiện tại có thể sử dụng được. `Adapter Pattern` thường chỉ đóng gói một đối tượng, trong khi `Facade Pattern` hoạt động với toàn bộ hệ thống con của các đối tượng.
* `Bridge Pattern`, `State Pattern` và `Strategy Patterns` (có thể được áp dụng như `Object Adapter`) có cấu trúc rất giống nhau. Thật vậy, tất cả các mẫu này đều dựa trên thành phần, tức là ủy quyền công việc cho các đối tượng khác. Tuy nhiên, tất cả đều giải quyết các vấn đề khác nhau. Một mẫu không chỉ là công thức để cấu trúc code của bạn theo một cách cụ thể. Nó cũng có thể thông báo cho các nhà phát triển khác về vấn đề mà mẫu này giải quyết được.

### Behavioral Design Pattern: Mediator

#### 1. Definition (Mediator Pattern)

**Mediator** là một mẫu thiết kế hành vi cho phép bạn giảm sự phụ thuộc giữa các đối tượng có liên quan bằng cách đặt chúng vào một đối tượng trung gian (mediator) đó chứa tất cả các logic giao tiếp. (**Mediator** is a *behavioral* design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.)

<center><img src = https://refactoring.guru/images/patterns/content/mediator/mediator.png></center>

#### 2. Problem Description

Giả sử bạn có hộp thoại để tạo và chỉnh sửa hồ sơ khách hàng. Nó bao gồm nhiều điều khiển biểu mẫu khác nhau như trường văn bản, hộp kiểm, nút, v.v.

<center><img src = https://refactoring.guru/images/patterns/diagrams/mediator/problem1-en.png></center>

Một số thành phần của biểu mẫu có thể tương tác với những thành phần khác. Ví dụ: việc chọn hộp kiểm “Tôi có một con chó” có thể hiển thị trường văn bản ẩn để nhập tên con chó. Một ví dụ khác là nút gửi phải xác thực giá trị của tất cả các trường trước khi lưu dữ liệu.

<center> <img src = https://refactoring.guru/images/patterns/diagrams/mediator/problem2.png> </center>

Bằng cách triển khai logic này trực tiếp bên trong code của các thành phần biểu mẫu, bạn làm cho các lớp của các thành phần này khó sử dụng hơn nhiều trong các dạng khác của ứng dụng. Ví dụ: bạn sẽ không thể sử dụng lớp ***CheckBox*** đó bên trong một biểu mẫu khác vì nó được kết hợp với trường văn bản của con chó. Bạn có thể sử dụng tất cả các lớp liên quan đến việc hiển thị biểu mẫu hồ sơ hoặc không sử dụng lớp nào cả.

#### 3. Solution  (Mediator Pattern)

`Mediator Pattern` đề nghị rằng bạn nên ngừng mọi liên lạc trực tiếp giữa các thành phần mà bạn muốn làm cho độc lập với nhau. Thay vào đó, các thành phần này phải cộng tác gián tiếp bằng cách gọi một đối tượng ***Mediator*** đặc biệt để chuyển hướng cuộc gọi đến các thành phần thích hợp. Kết quả là các thành phần chỉ phụ thuộc vào một lớp trung gian duy nhất thay vì được ghép nối với hàng chục thành phần khác.

Trong ví dụ của chúng tôi với biểu mẫu chỉnh sửa hồ sơ, chính class ***Dialog*** có thể đóng vai trò như là một class ***Mediator***. Rất có thể, class ***Dialog*** đã biết tất cả các thành phần phụ của nó, vì vậy bạn thậm chí sẽ không cần đưa các phần phụ thuộc mới vào lớp này.

<center><img src = https://refactoring.guru/images/patterns/diagrams/mediator/solution1-en.png></center>

Sự thay đổi đáng kể nhất xảy ra với các thành phần biểu mẫu thực tế. Hãy xem xét nút gửi. Trước đây, mỗi lần người dùng nhấp vào nút, nó phải xác thực giá trị của tất cả các thành phần biểu mẫu riêng lẻ. Bây giờ công việc duy nhất của nó là thông báo cho class ***Dialog*** về lần nhấp chuột. Khi nhận được thông báo này, ***Dialog*** sẽ tự thực hiện xác thực hoặc chuyển nhiệm vụ cho từng phần tử. Do đó, thay vì bị ràng buộc với hàng tá phần tử biểu mẫu, nút này chỉ phụ thuộc vào class ***Dialog***.

Bạn có thể tiến xa hơn và làm cho sự phụ thuộc trở nên lỏng lẻo hơn bằng cách trích xuất giao diện chung cho tất cả các loại ***Dialog***. Giao diện sẽ khai báo phương thức thông báo mà tất cả các thành phần của biểu mẫu có thể sử dụng để thông báo cho ***Dialog*** về các sự kiện xảy ra với các thành phần đó. Do đó, nút gửi của chúng tôi giờ đây có thể hoạt động với bất kỳ ***Dialog*** nào triển khai giao diện đó.

Bằng cách này, `Mediator Pattern` cho phép bạn đóng gói một mạng lưới quan hệ phức tạp giữa các đối tượng khác nhau bên trong một đối tượng `Mediator` duy nhất. Một lớp càng có ít sự phụ thuộc thì việc sửa đổi, mở rộng hoặc tái sử dụng lớp đó càng dễ dàng hơn.

#### 4. Real-World Analogy (Phân tích thực tế)

<center><img src = https://refactoring.guru/images/patterns/diagrams/mediator/live-example.png></center>

Phi công của các máy bay tiếp cận hoặc rời khỏi khu vực kiểm soát sân bay không liên lạc trực tiếp với nhau. Thay vào đó, họ nói chuyện với một nhân viên kiểm soát không lưu, người ngồi trên một tòa tháp cao gần đường băng. Nếu không có người kiểm soát không lưu, các phi công sẽ cần phải biết về mọi máy bay ở khu vực lân cận sân bay, thảo luận về các ưu tiên hạ cánh với một ủy ban gồm hàng chục phi công khác. Điều đó có thể sẽ làm tăng vọt số liệu thống kê về tai nạn máy bay.

Tháp không cần phải điều khiển toàn bộ chuyến bay. Nó chỉ tồn tại để thực thi các hạn chế trong khu vực nhà ga vì số lượng các bên liên quan ở đó có thể quá tải đối với một phi công.

#### 5. Structure (Mediator Design Pattern)

<center><img src = https://refactoring.guru/images/patterns/diagrams/mediator/structure-indexed.png></center>

1. `Components` là các lớp khác nhau chứa một số logic nghiệp vụ. Mỗi `Component` có một tham chiếu đến một `Mediator`, được khai báo với loại `Mediator Interface`. `Component` này không nhận biết được lớp thực tế của `Mediator`, vì vậy bạn có thể sử dụng lại `Component` đó trong các chương trình khác bằng cách liên kết nó với một `Mediator` khác.

2. `Mediator Interface` khai báo các phương thức giao tiếp với `Components`, thường chỉ bao gồm một phương thức thông báo duy nhất. `Components` có thể chuyển bất kỳ ngữ cảnh nào làm đối số của phương thức này, bao gồm cả các đối tượng của chính chúng, nhưng chỉ theo cách không xảy ra sự ghép nối giữa `Component` nhận và lớp của người gửi.

3. `Concrete Mediators` đóng gói các mối quan hệ giữa các thành phần khác nhau. `Concrete Mediators` thường lưu giữ các tham chiếu đến tất cả các thành phần mà họ quản lý và đôi khi thậm chí còn quản lý vòng đời của chúng.

4. `Components` không được nhận thức được các `Components` khác. Nếu có điều gì quan trọng xảy ra bên trong hoặc với một `Component` thì `Component` đó chỉ được thông báo cho `Mediator`. Khi `Mediator` nhận được thông báo, nó có thể dễ dàng xác định người gửi `(sender)`, điều này có thể vừa đủ để quyết định `Component` nào sẽ được kích hoạt đáp lại.

Từ góc nhìn của một `Components`, tất cả trông giống như một hộp đen hoàn toàn. Người gửi `(sender)` không biết ai sẽ là người xử lý yêu cầu của mình và người nhận `(reciever)` không biết ai đã gửi yêu cầu ngay từ đầu.

#### 6. Application (Mediator Design Pattern)

* Sử dụng `Mediator Pattern` khi khó thay đổi một số lớp vì chúng được liên kết chặt chẽ với nhiều lớp khác.
  * Mẫu này cho phép bạn trích xuất tất cả các mối quan hệ giữa các lớp thành một lớp riêng biệt, tách biệt mọi thay đổi đối với một thành phần cụ thể khỏi các thành phần còn lại.
* Sử dụng `Mediator Pattern` khi bạn không thể sử dụng lại một thành phần trong một chương trình khác vì nó quá phụ thuộc vào các thành phần khác.
  * Sau khi bạn áp dụng `Mediator Pattern` , các `component` riêng lẻ `(individuals)` sẽ không nhận biết được các `component` khác. Chúng vẫn có thể liên lạc với nhau, dù là gián tiếp, thông qua một đối tượng `Mediator`. Để sử dụng lại một thành phần trong một ứng dụng khác, bạn cần cung cấp cho `component` đó một lớp `Mediator` mới.
* Sử dụng `Mediator Pattern` khi bạn thấy mình đang tạo ra rất nhiều lớp con thành phần chỉ để sử dụng lại một số hành vi (*behavior*) cơ bản trong nhiều ngữ cảnh khác nhau.
  * Vì tất cả các mối quan hệ giữa các `component` đều được chứa trong `Mediator`, nên thật dễ dàng xác định những cách hoàn toàn mới để các thành phần này cộng tác bằng cách giới thiệu các lớp `Mediator` mới mà không cần phải tự thay đổi các thành phần.

#### 7. How To Implement (Mediator Design Pattern)

1. Xác định một nhóm các lớp được liên kết chặt chẽ sẽ được hưởng lợi từ việc độc lập hơn (ví dụ: để bảo trì dễ dàng hơn hoặc tái sử dụng các lớp này đơn giản hơn).
2. Khai báo `Mediator Interface` và mô tả giao thức liên lạc mong muốn giữa các `Mediator` và các `Components` khác nhau. Trong hầu hết các trường hợp, chỉ cần một phương pháp duy nhất để nhận thông báo từ các thành phần là đủ. Giao diện này rất quan trọng khi bạn muốn sử dụng lại các lớp thành phần trong các ngữ cảnh khác nhau. Miễn là thành phần này hoạt động với `Mediator` của nó thông qua giao diện chung, bạn có thể liên kết thành phần đó với cách triển khai `Mediator` khác.
3. Thực hiện class `Concrete Mediator`. Xem xét việc lưu trữ các tham chiếu đến tất cả các thành phần bên trong `Mediator`. Bằng cách này, bạn có thể gọi bất kỳ thành phần nào từ các phương thức của class `Mediator`.
4. Bạn có thể tiến xa hơn nữa và yêu cầu `Mediator` chịu trách nhiệm tạo và hủy các đối tượng `Components`. Sau đó, `Mediator` có thể giống một `Factory Pattern` hoặc một `Facade Pattern`.
5. `Components` nên lưu trữ một tham chiếu đến đối tượng `Mediator`. Kết nối thường được thiết lập trong hàm tạo của `component`, trong đó một đối tượng `Mediator` được truyền dưới dạng đối số.
6. Thay đổi code của các `components` để chúng gọi phương thức thông báo của `Mediator Pattern` thay vì các phương thức trên các `components` khác. Trích xuất code liên quan đến việc gọi các thành phần khác vào class `Mediator`. Thực thi code này bất cứ khi nào `Mediator` nhận được thông báo `(notifications)` từ `component` đó.

#### 8. Pros and Cons (Mediator Design Pattern)

|Advantages|Disadvantages|
|----------|-------------|
|*Single Responsibility Principle* : Bạn có thể trích xuất thông tin liên lạc giữa các `components` khác nhau vào một nơi duy nhất, giúp dễ hiểu và duy trì hơn.|Theo thời gian, `Mediator` có thể tiến hóa thành [God Object](https://en.wikipedia.org/wiki/God_object).|
|*Open/Closed Principle* : Bạn có thể giới thiệu các `Mediator` mới không cần thay đổi code của các `components` hiện có.||
|Bạn có thể giảm sự ghép nối giữa các thành phần khác nhau của chương trình.||
|Bạn có thể tái sử dụng các thành phần riêng lẻ dễ dàng hơn.||

#### 9. Relations with Other Patterns (Mediator Design Pattern)

* `Chain of Responsibility`, `Command`, `Mediator` và `Observer` giải quyết nhiều cách khác nhau để kết nối người gửi và người nhận yêu cầu:
  * `Chain of Responsibility` chuyển yêu cầu một cách tuần tự dọc theo chuỗi động những người nhận tiềm năng cho đến khi một trong số họ xử lý yêu cầu đó.
  * `Command` thiết lập kết nối một chiều giữa người gửi và người nhận.
  * `Mediator` loại bỏ các kết nối trực tiếp giữa người gửi và người nhận, buộc họ phải giao tiếp gián tiếp thông qua một đối tượng `Mediator`.
  * `Observer` cho phép người nhận tự động đăng ký và hủy đăng ký nhận yêu cầu.
* `Facade` và `Mediator` có công việc tương tự nhau: chúng cố gắng tổ chức sự cộng tác giữa nhiều lớp được liên kết chặt chẽ.
  * `Facade` xác định giao diện đơn giản hóa cho hệ thống con của các đối tượng, nhưng nó không giới thiệu bất kỳ chức năng mới nào. Bản thân hệ thống con không biết về `Facade`. Các đối tượng trong hệ thống con có thể giao tiếp trực tiếp.
  * `Mediator` tập trung giao tiếp giữa các thành phần của hệ thống. Các thành phần chỉ biết về đối tượng `Mediator` và không giao tiếp trực tiếp.
* Sự khác biệt giữa `Mediator Pattern` và `Observer` thường khó nắm bắt. Trong hầu hết các trường hợp, bạn có thể triển khai một trong các mẫu này; nhưng đôi khi bạn có thể áp dụng cả hai cùng một lúc. Hãy xem làm thế nào chúng ta có thể làm điều đó.
  * Mục tiêu chính của `Mediator Pattern` là loại bỏ sự phụ thuộc lẫn nhau giữa một tập hợp các thành phần hệ thống. Thay vào đó, các `components` này trở nên phụ thuộc vào một đối tượng `Mediator` duy nhất. Mục tiêu của `Observer Pattern` là thiết lập các kết nối một chiều động giữa các đối tượng, trong đó một số đối tượng đóng vai trò là cấp dưới của đối tượng khác.
  * Có một cách triển khai phổ biến `Mediator Pattern` dựa trên `Observer Pattern`. Đối tượng `Mediator` đóng vai trò là nhà xuất bản và các thành phần đóng vai trò là người đăng ký có thể đăng ký và hủy đăng ký khỏi các sự kiện của `Mediator`. Khi `Mediator` được triển khai theo cách này, nó có thể trông rất giống với `Observer`.
  * Khi bạn gặp khó khăn trong việc chọn lựa, hãy nhớ rằng bạn có thể triển khai `Mediator Pattern` theo những cách khác. Ví dụ: bạn có thể liên kết vĩnh viễn tất cả các `components` với cùng một đối tượng `Mediator`. Việc triển khai này sẽ không giống với `Observer` nhưng vẫn sẽ là một phiên bản của `Mediator Pattern`.
  * Bây giờ hãy tưởng tượng một chương trình trong đó tất cả các thành phần đều trở thành nhà xuất bản, cho phép kết nối động với nhau. Sẽ không có đối tượng trung gian tập trung mà chỉ có một nhóm người quan sát phân tán.

------------------

## ASSIGNMENT TASKS

| Student ID | Full name       | Group | Task    | Requirements | Final Products | Main responsibility| 
| ---------- | ----------------| ----- | --------| -------------|----------------|--------------------|
| 22127174   | Ngo Van Khai    | OOP   |Code (assistant) + Write the report (edit + content $\to$ mentor)| Should do carefully about content (definition + explain project structure + explain code project in  report) + share link word document with members|Source code + Report| Report |
| 22127322   | Le Phuoc Phat   | OOP   |Code (assistant) + Video project (edit video $\to$ mentor about editing) + report (edit) + manager|Edit video + edit report + edit source code|Source Code + Video + Report| Video|
| 22127388   | To Quoc Thanh   | OOP   |Code (mentor) + Video project (representatives $\to$ mentor about presenting) + write the report (assistant + help KhaiNgo write the report) + Draw UML| Code carfully the structural and behavior design pattern (main ideas + all classes) and then present your ideas with the members of team| Source code + Video + Report + UML|Code + UML|
| 22127441   | Thai Huyen Tung | OOP   |Code (edit code + comment the code + explain code carefully) + do the slides (edit + content $\to$ mentor)|Do slides on the canvas and share the link of slide with the members of team|Source code + Slide|Slides|

Please follow the link below to see the details of the assignment tasks:

* **Slides on Canvas** : [Link of Slides](https://www.canva.com/design/DAF15JPCa78/dqBIAPuwKWfjuz2uXGdgTA/edit?utm_content=DAF15JPCa78&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)
* **Report** : [Link on Report](https://studenthcmusedu-my.sharepoint.com/:w:/g/personal/22127322_student_hcmus_edu_vn/Ee7hBxCzbflCicQHjYRumQUB2ig6sBtjKew-dgqIOUgYmA?e=ei5pMI)
* **Source code** : [Link on Source code](<https://github.com/PhuocPhat1005/DesignPatternOOP.git>)
* **Video** : [Link on Video](https://www.capcut.com/s/CZSTDa1aJJEy7NAR/)
* **UML Drawing** : [Link on UML](https://drive.google.com/file/d/16kzgobSHHAG5baFU5Res1TjHi__2yT6R/view?usp=sharing)
* **Google Drive :**  [Link on Google Drive](<https://drive.google.com/drive/folders/1U5lKAIU72h_7iKDdAQJ7TRZDnYc344dc?usp=sharing>)

**MUST BE DONE BEFORE 23:59:00 DECEMBER **$20^{th}$**, 2023**
