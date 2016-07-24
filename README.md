#Calculating K-Mers Frequency

##Task

Given a FASTQ file, produce a list, sorted by frequency, of the 25 most frequent DNA-k-mers (a substring of length k) of length 30 in that file. You are allowed to use libraries, as long as their purpose is not specifically to count k-mers. A valid solution must include a build script that builds a working executable that we can test on either Mac OS X or Linux.

For reference, any fastq file from the 1000 Genomes project will serve as a valid example. For instance, these(ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/phase3/data/HG01595/sequence_read/) are the fastq files available for HG01595. Note that we are only interested in the actual DNA sequences, which are stored in the second line of each entry (Wikipedia has a good description of the format). The sequences are independent and should not be concatenated.

##Requirements

The program must compile and run on Mac or Linux. If you’re on Windows, consider testing using a Linux virtual machine. Virtualbox and Ubuntu are free.

The program should accept inputs via command line arguments only. The user should be able to select the input file, the k-mer size and the number of top k-mers. Exposing other, internal parameters required by the chosen algorithm is at the discretion of the coder.

##Okay:


`./myprogram --filename big.fastq --kmersize 30 --topcount 25`

`./myprogram big.fastq 30 25`

##Not okay:

"Please enter a filename" (don’t have anything that waits for user)

`ifstream("hardcoded_filepath.fastq");`

##Usage:
`g++ SevenBridges.cpp -o sevenbridges` 

`./sevenbridges -f test.fastq -k 30 -t 10`

or

`./sevenbridges --f test.fastq --k 30 --t 10`

or

`./sevenbridges test.fastq 30 10`

