fsize=$(wc -c < os.img)
sectors=$(($fsize / 512))

echo "Kernel: $sectors sectors"
