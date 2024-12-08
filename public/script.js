function showMeowdal() {
  const modal = document.getElementById("meowdal");
  modal.style.display = "flex";

  setTimeout(() => {
    modal.style.display = "none";
  }, 1000);
}
