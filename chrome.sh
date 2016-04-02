alias bo='echo $BOARD'
alias bs='./setup_board --board=${BOARD}'
alias bp='./build_packages --board=${BOARD}'
alias bi='./build_image --board=${BOARD} --noenable_rootfs_verification test'

ccache --max-size=10G
export CCACHE_DIR=/var/cache/distfiles/ccache

export TIMEFORMAT="%R"
echo $1
export BOARD=$1
