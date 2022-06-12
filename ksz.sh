if [ ! -f "os.img" ]; then
    echo "file os.img does not exist, run **make img** first"
else
    fsize=$(wc -c < os.img)
    sectors=$(($fsize / 512))
    echo "Kernel: $sectors sectors"
fi
