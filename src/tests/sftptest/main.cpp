#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>

#include <QtCore/QCoreApplication>


int main(int argc, char *argv[])
{
	// INIT
	ssh_session sshsession = ssh_new();

	ssh_options_set(sshsession, SSH_OPTIONS_HOST, "192.168.1.117");

	int conn = ssh_connect(sshsession);

	int key = ssh_userauth_password(sshsession, "root", "password");

	sftp_session sftpsession = sftp_new(sshsession);

	int sftpinit = sftp_init(sftpsession);

	// DIR READ
	sftp_dir dir = sftp_opendir(sftpsession, "/root/");

	sftp_attributes file;
	while((file = sftp_readdir(sftpsession, dir))) {

		if (file->type == 1) // 1 == file; 2 == dir
		{
			// todo..
		}
	}

	// FILE READ
	sftp_file l_file = sftp_open(sftpsession, "/root/test.txt", O_RDONLY, 0);
	sftp_attributes attr = sftp_fstat(l_file);
	QByteArray l_ba;
	l_ba.resize(attr->size);
	ssize_t readed = sftp_read(l_file, l_ba.data(), attr->size);
	sftp_close(l_file);

	return 0;
}
