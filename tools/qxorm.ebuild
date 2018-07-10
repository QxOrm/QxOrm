# Copyright 1999-2010 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v3
# $Header: /var/cvsroot/gentoo-x86/dev-cpp/qxorm/qxorm-1.4.3-r1.ebuild,v 1.4.3-r1 2011/04/04 $

EAPI="2"

inherit qt4-r2

DESCRIPTION="C++ Object Relational Mapping library"
HOMEPAGE="http://www.qxorm.com/"
SRC_URI="http://www.qxorm.com/version/QxOrm_${PV}.zip"
S=${WORKDIR}/QxOrm

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 x86"

IUSE="gui"

RDEPEND="x11-libs/qt-sql:4
	gui? ( x11-libs/qt-gui:4 )"

DEPEND="${RDEPEND}"

PACKNAME="QxOrm"

PATCHES=(
    "${FILESDIR}/${P}-20110413.patch"
)

src_configure() {
	local conf_add
	conf_add="${conf_add} $(use_enable gui)"

	eqmake4 "${PACKNAME}.pro" \
		CONFIG+="${conf_add}" \
		|| die "eqmake4 failed."
}

src_compile() {
	default
	emake all || die "make all failed"
}

src_install() {
	emake install  DESTDIR="${D}"|| die "make install failed"
	# deploy headers
	dodir /usr/include/${PACKNAME} || die "create include directory failed"
	insinto /usr/include/${PACKNAME}
	doins -r ${S}/include/* || die "headers copy failed"
	doins -r ${S}/inl/* || die "inline headers copy failed"
	find "${D}"/usr/include -type f -name "*.h" -exec sed -i 's,../inl/,,g' {} \;
	find "${D}"/usr/include -type f -name "*.inl" -exec sed -i 's,../inl/,,g' {} \;

	# deploy library
	insinto /usr/lib
	#doins ${S}/lib/libQxOrm.a || die "copy library failed"
	#doins ${S}/lib/libQxOrm.la || die "copy library failed"
	exeinto /usr/lib
	doexe ${S}/lib/libQxOrm.so.1.0.0 || die "copy library failed"

	# rename library
	LIBDIR=`ls "${D}"/usr/|grep lib`
	mv "${D}"/usr/${LIBDIR}/lib${PACKNAME}.so.1.0.0 "${D}"/usr/${LIBDIR}/lib${PACKNAME}-1.1.so.${PV} || die "rename <lib${PACKNAME}-1.1.so.4.0.0> library failed"
	ln -sf lib${PACKNAME}-1.1.so.${PV} "${D}"/usr/${LIBDIR}/lib${PACKNAME}-1.1.so || die "create symbolic link <lib${PACKNAME}-1.1.so> failed"
	ln -sf lib${PACKNAME}-1.1.so.${PV} "${D}"/usr/${LIBDIR}/lib${PACKNAME}.so || die "create symbolic link <lib${PACKNAME}.so> failed"
}
