const searchInput = document.getElementById("searchInput");

const titleInput = document.getElementById("bookTitle");
const statusInput = document.getElementById("bookStatus");
const addBookBtn = document.getElementById("addBookBtn");

const bookList = document.getElementById("bookList");
const filterStatus = document.getElementById("filterStatus");
const emptyState = document.getElementById("emptyState");

let books = JSON.parse(localStorage.getItem("books")) || [];

function saveBooks() {
    localStorage.setItem("books", JSON.stringify(books));
}

function updateCounts() {
    document.getElementById("toReadCount").textContent =
        books.filter(book => book.status === "To Read").length;

    document.getElementById("readingCount").textContent =
        books.filter(book => book.status === "Reading").length;

    document.getElementById("doneCount").textContent =
        books.filter(book => book.status === "Done").length;
}

function getBadgeClass(status) {
    if (status === "To Read") return "to-read";
    if (status === "Reading") return "reading";
    return "done";
}

function renderBooks() {
    const filter = filterStatus.value;
    const searchText = searchInput.value.toLowerCase();

    let filteredBooks = books;

    if (filter !== "All") {
        filteredBooks = filteredBooks.filter(
            book => book.status === filter
        );
    }

    if (searchText) {
        filteredBooks = filteredBooks.filter(
            book => book.title.toLowerCase().includes(searchText)
        );
    }

    bookList.innerHTML = "";

    if (books.length === 0) {
        emptyState.style.display = "block";
    } else {
        emptyState.style.display = "none";
    }

    filteredBooks.forEach((book, index) => {
        const card = document.createElement("div");
        card.className = "book-card";

        card.innerHTML = `
            <div class="book-title">${book.title}</div>

            <span class="badge ${getBadgeClass(book.status)}">
                ${book.status}
            </span>

            <select class="status-select" data-id="${book.id}">
                <option value="To Read" ${book.status === "To Read" ? "selected" : ""}>
                    To Read
                </option>
                <option value="Reading" ${book.status === "Reading" ? "selected" : ""}>
                    Reading
                </option>
                <option value="Done" ${book.status === "Done" ? "selected" : ""}>
                    Done
                </option>
            </select>

            <button class="delete-btn" data-id="${book.id}">
                Delete
            </button>
        `;

        bookList.appendChild(card);
    });

    document.querySelectorAll(".status-select").forEach(select => {
        select.addEventListener("change", function () {
            const id = Number(this.dataset.id);

            const book = books.find(book => book.id === id);

            if (book) {
                book.status = this.value;
            }

            saveBooks();
            updateCounts();
            renderBooks();
        });
    });

    updateCounts();
}

bookList.addEventListener("click", event => {
    const button = event.target.closest(".delete-btn");

    if (!button) return;

    const confirmed = confirm("Are you sure you want to delete this book?");

    if (!confirmed) return;

    const id = Number(button.dataset.id);
    books = books.filter(book => book.id !== id);

    saveBooks();
    renderBooks();
});

addBookBtn.addEventListener("click", () => {
    const title = titleInput.value.trim();

    if (!title) {
        alert("Please enter a book title.");
        return;
    }

    // Check for duplicate title (case-insensitive)
    const bookExists = books.some(
        book => book.title.toLowerCase() === title.toLowerCase()
    );

    if (bookExists) {
        alert("This book is already in your reading list.");
        return;
    }

    books.push({
        id: Date.now(),
        title: title,
        status: statusInput.value
    });

    saveBooks();

    titleInput.value = "";

    renderBooks();
});

searchInput.addEventListener("input", renderBooks);

filterStatus.addEventListener("change", renderBooks);

renderBooks();